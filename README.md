# yri_microscope

Core firmware library for the YRI Microscope handheld device.

## Purpose

`yri_microscope` provides the shared platform code for Microscope, including:

- display and UI support
- keyboard/input handling
- SD-backed storage
- simplified web content fetch
- document/wiki viewing
- Lua scripting hooks
- future USB/file interaction helpers

## Design goals

- modular
- lightweight
- embedded-friendly
- app-oriented
- able to operate offline with SD as primary storage
- web used as a simple content source, not a full browser

## Major areas

- `core/` runtime and common interfaces
- `device/` hardware-facing managers
- `net/` simplified HTTP/content pull
- `storage/` filesystem and SD helpers
- `scripting/` Lua integration
- `content/` parsers and document models
- `apps/` user-facing Microscope apps
