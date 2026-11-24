# WHY?
MY CURRENT DESKTOP ENVIRONMENT (KDE) LACKS A GREYSCALE FILTER. SOMETIMES I AM RUNNING OUT OF TIME, YET I CONTINUE TO WASTE TIME. BECAUSE COLORS ARE OVERSTIMULATING. THAT'S WHY PRE-2000 PROGRAMMERS WERE SO DAMM GOOD.

# WHY HARDWARE LEVEL?
BECAUSE COMPOSITOR-LEVEL EFFECTS INTRODUCE ANOTHER PROCESSING LAYER AND CAN SOMETIMES BE GLITCHY AND CAN HAVE COMPATIBILITY ISSUES WITH DESKTOP ENVIRONMENT. SOMETIMES IT WON'T WORK ON VIDEOS, PICTURES ETC.

┌──────────────────────────────────────────────────────┐
│                  USER SPACE                          │
│                                                      │
│  Applications: Browser, Terminal, KDE Applications   │
│                         │                            │
│                         ▼                           │
│               KDE Wayland / KWin                     │
│               Display Compositor                     │
│                                                      │
│  Not modifying KWin currently.                       │
└─────────────────────────┬────────────────────────────┘
                          │
══════════════════════════╪══════════════════════════════
                          │
┌─────────────────────────▼────────────────────────────┐
│                   KERNEL SPACE                        │
│                                                       │
│                 Linux DRM / KMS                       │
│                                                       │
│  DRM: Direct Rendering Manager                        │
│  KMS: Kernel Mode Setting                             │
│                                                       │
│  Manages display resources and display configuration. │
│                         │                             │
│                         ▼                            │
│                  Intel i915 Driver                    │
│                                                       │
│  Intel integrated graphics driver.                    │
│                         │                             │
│                         ▼                            │
│                  DRM Atomic API                       │
│                                                       │
│  Where display properties are configured.             │
│                         │                             │
│                         ▼                            │
│  ┌───────────────────────────────────────────────┐    │
│  │              CRTC 60                          │    │
│  │              Internal eDP-1 Display           │    │
│  │                                               │    │
│  │  Properties discovered using modetest:        │    │
│  │                                               │    │
│  │  DEGAMMA_LUT  (Property 26)                   │    │
│  │  GAMMA_LUT    (Property 29)                   │    │
│  │  CTM          (Property 28)  ◄── TARGET      │    │
│  │                                               │    │
│  │  CTM: 3 × 3 Color Transformation Matrix       │    │
│  │                                               │    │
│  │  RGB input → Grayscale transformation        │    │
│  └───────────────────────┬───────────────────────┘    │
└──────────────────────────┼─────────────────────────── ┘
                           │
═══════════════════════════╪════════════════════════════
                           │
┌──────────────────────────▼───────────────────────────┐
│                    HARDWARE                           │
│                                                       │
│             Intel Integrated GPU                      │
│                                                       │
│          Hardware Display Color Pipeline              │
│                                                       │
│                Monochrome Output                      │
│                                                       │
│                 ThinkPad T480                         │
└──────────────────────────────────────────────────────-┘


                CURRENT EXPERIMENT
                ──────────────────

  Tool:       libdrm
  Interface:  DRM Atomic API
  Driver:     i915
  Target:     CRTC 60
  Property:   CTM (28)
  Operation:  Apply 3 × 3 grayscale matrix
  Test:       Successful with SDDM stopped
  
  WORKS INSIDE TELETYPEWRITER TTY
