#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <xf86drm.h>
#include <xf86drmMode.h>

int main(int argc, char **argv) {
    int fd = drmOpen("i915", NULL);
    if (fd < 0) return 1;

    drmSetClientCap(fd, DRM_CLIENT_CAP_ATOMIC, 1);

    uint64_t m[9] = {0};

    if (argc > 1 && !strcmp(argv[1], "reset")) {
        drmModeAtomicReq *r = drmModeAtomicAlloc();
        drmModeAtomicAddProperty(r, 60, 28, 0);
        int ret = drmModeAtomicCommit(fd, r, 0, NULL);
        drmModeAtomicFree(r);
        drmClose(fd);
        return ret != 0;
    }

    double v[] = {0.2126, 0.7152, 0.0722};
    for (int i = 0; i < 9; i++)
        m[i] = (uint64_t)(v[i % 3] * 4294967296.0 + 0.5);

    uint32_t blob;
    if (drmModeCreatePropertyBlob(fd, m, sizeof(m), &blob))
        return 2;

    drmModeAtomicReq *r = drmModeAtomicAlloc();
    drmModeAtomicAddProperty(r, 60, 28, blob);

    int ret = drmModeAtomicCommit(fd, r, 0, NULL);

    drmModeAtomicFree(r);
    drmModeDestroyPropertyBlob(fd, blob);
    drmClose(fd);

    return ret != 0;
}
