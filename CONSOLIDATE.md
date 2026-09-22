# Consolidation notes (Nil Object → laulandn/sdl2macos9)

**Branch:** `n0stalgia-sys6`  
**Base:** `laulandn/sdl2macos9` `master` @ `3270dbd` (“Some updates…”, 2026-09-21 UTC / 2026-09-22 AEST)  
**Long-term goal:** TinyGL / OpenGL on **System 6 / 68k**

Do **not** treat this file as a finished Sys6 port. It records provenance, what is already upstream, what remains on Mac-local trees, and how to build the Sys6-oriented profile.

## Trees inventoried

| Tree | Role | Status vs laulandn `master` |
|------|------|-----------------------------|
| `https://github.com/laulandn/sdl2macos9` | Canonical upstream | Tip `3270dbd` — **includes TinyGL hooks + doctashay merge** |
| `https://github.com/doctashay/sdl2macos9` `master` | Fork tip | **Behind** by 7 commits; merge-base is `7b1a970` (2025-08-27) |
| `doctashay/sdl2macos9` `os9-fixes` | Half-Life / AGL work | Already rolled into laulandn (`089c9c2` “Merged in work by doctashay…”) |
| `cacaosteve/sdl2macos9` | Mirror fork | No unique tip (stuck at older laulandn) |
| Mac `~/Developer/bots/grok/sdl2macos9` | User clone (origin laulandn) | Survey said **behind 1**, dirty: `README.md`, `SDL-main/include/SDL_config_macosclassic.h` — **not readable from this agent box** |
| Mac `~/Downloads/sdl2macos9` | Aug working tree | May lack `.git` — **not readable from this agent box** |
| Mac `~/Developer/bots/grok/sdl2-sys6` | Sys6-oriented (CMake/Makefile, game/maelstrom/lastmac/dist) | **not readable from this agent box** |

### Upstream already unique / relevant (present in `3270dbd`)

- **TinyGL path (present, optional):** `SDL_MACOSCLASSIC_OSGL` + `SDL_MACOSCLASSIC_TINYGL` in `macosgl.c` / `macglos.c` (`#include "GL/ostinygl.h"`, `ostgl_create_context`, …). Makefile lines are **commented**; default m68k/PPC builds use **AGL**.
- **Mesa OSGL alternate** (also commented): `SDL_MACOSCLASSIC_MESAGL`.
- **doctashay OS9 video/audio/AGL** merged; README updated accordingly.
- Extra targets (Palm/PS1/PS2/PSP/OpenStep) — **out of scope** for Sys6 PR; leave untouched.
- Sprockets optional via `SDL_MACOSCLASSIC_INPUTSPROCKET` / `DRAWSPROCKET` (enabled in stock `Makefile.r68`).

### What this branch adds

1. `CONSOLIDATE.md` (this file) — provenance + TinyGL/Sys6 goal.
2. `SDL-main/Makefile.r68.sys6` — Retro68 **m68k** profile aimed at System 6-class hosts:
   - **no** InputSprocket / DrawSprocket / AGL
   - **yes** OSGL + TinyGL (`-DSDL_MACOSCLASSIC_OSGL=1 -DSDL_MACOSCLASSIC_TINYGL=1`)
   - expects external TinyGL headers/libs (see Build)
3. README pointer to this doc and the Sys6 TinyGL goal.

### Not yet merged (blocked: Mac paths unreachable)

Executor subagent could not Shell `machineId=92a1ae29-…` or CopyToBox Mac trees. Parent/gitmon must still:

1. Diff Mac dirty files vs `3270dbd` and fold any Sys6/`SDL_config_macosclassic.h` / README edits worth keeping.
2. Lift **unique** bits from `sdl2-sys6` (CMake/Makefile wrappers, game/maelstrom/lastmac/dist) — prefer **thin** build wrappers + docs over vendoring large game binaries.
3. Re-check `~/Downloads/sdl2macos9` Aug builds for video/TinyGL deltas not in git.

## TinyGL status

| Item | Status |
|------|--------|
| SDL TinyGL/OSGL hooks | **Present** upstream (`macosgl.c` / `macglos.c`) |
| Default build | AGL (TinyGL **off**) |
| Vendored TinyGL sources | **Missing** in-repo (expected at `$(HOME)/tinygl` or `TINYGL_ROOT`) |
| Sys6 profile makefile | **Added** here (`Makefile.r68.sys6`) |
| Runtime on System 6.0.8 | Proven for 2D SDL2 games (nilSDL2 / CrystalPlus); **GL/TinyGL on Sys6 not finished** |

## Build (68k Retro68)

Stock classic (Sys7+/sprockets/AGL):

```sh
make -f Makefile.r68
# or
make -C SDL-main -f Makefile.r68
```

Sys6-oriented TinyGL profile (this branch):

```sh
# TinyGL must be built/installed separately; headers need GL/ostinygl.h
export TINYGL_ROOT=${TINYGL_ROOT:-$HOME/tinygl}
make -C SDL-main -f Makefile.r68.sys6
make -C SDL-main -f Makefile.r68.sys6 install   # optional → Retro68 prefix
```

PPC remains `Makefile.r68ppc` (AGL). A Sys6 TinyGL story is **68k-first**.

## PR guidance for gitmon

- **PR target:** `laulandn/sdl2macos9` `master`
- **Head branch:** `n0stalgia-sys6` (push to Nil Object / n0stalgia fork if available; else push from Mac clone after syncing this commit)
- **Do not** force-push `laulandn/master`
- **Do not** open the PR from random agents — gitmon owns the PR
- Suggested title: `n0stalgia: Sys6 TinyGL build profile + consolidation notes`
- Suggested body: point at `CONSOLIDATE.md`; note Mac-local `sdl2-sys6` still pending second PR if needed

## Suggested commit message

```
n0stalgia-sys6: document consolidation; add TinyGL Sys6 m68k Makefile

Base laulandn/master (TinyGL hooks already upstream). Add CONSOLIDATE.md
provenance and Makefile.r68.sys6 (no sprockets/AGL; OSGL+TinyGL). Mac-local
sdl2-sys6 / Downloads trees still need a follow-up merge when reachable.
```

## Mac fold-in (2026-09-22 AEST)

Merged dirty clone + Sys6 overlay onto this branch:

- `SDL_MACOSCLASSIC_SYS6` path: `Makefile.r68sys6`, `macvideo_sys6.c`, `macevents_sys6.c`
- Indexed/1-bit depth helpers (`Mac_SDLFormatForDepth`), timer/spin/fillrect/keys tweaks
- Separate tree `~/Developer/bots/grok/sdl2-sys6` remains a **game/host wrapper** (Crystal Plus, LastMac) — not vendored here; build against this SDL overlay

TinyGL still needs external `TINYGL_ROOT` / `$(HOME)/tinygl`.

