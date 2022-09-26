NotSoPrivate
================

[![Build Status](https://github.com/flagersgit/NotSoPrivate/workflows/CI/badge.svg?branch=master)](https://github.com/flagersgit/NotSoPrivate/actions)

[Lilu](https://github.com/acidanthera/Lilu) Kernel extension which enables private logging without the need for a provisioning profile by modifying the commpage directly.

#### Boot arguments

- `-nspoff` (or `-liluoff`) to disable
- `-nspdbg` (or `-liludbgall`) to enable verbose logging (in DEBUG builds)
- `-nspbeta` (or `-lilubetaall`) to enable on macOS newer than 13

### Credits

- [Apple](https://www.apple.com) for macOS
- [Flagers](https://github.com/flagersgit) for this kernel extension
- [vit9696](https://github.com/vit9696) for [Lilu.kext](https://github.com/acidanthera/Lilu)
