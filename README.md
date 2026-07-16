# abls-agent-shelly

Containerized Shelly runtime for Abls-Habitat.

## Current implementation status

- Runtime skeleton based on ABLS-AGENT-LIBS
- Facility fixed to `shelly`
- Prefix initialized from `agent_tech_id`
- Config bootstrap via Json_read_config using precedence:
  1. Environment variables (ABLS_*)
  2. /etc/abls-habitat-agent.conf
  3. Defaults in code

Supported Shelly devices:

- `shellyproem50`
- `shellypro3em`

## Build

```sh
./install_deps.sh
./build.sh
```

## Packaging RPM

```sh
./build_rpm.sh
```

Produces runtime RPM package in `build/`.

## Packaging DEB

```sh
./build_apt.sh --dist bookworm --no-sign
./build_apt.sh --dist trixie --no-sign
```

Produces runtime DEB package and copies normalized artifacts to:

- `build/deb/<suite>/<arch>/`

## Release bump + publication

```sh
./bump.sh 1.2.3
```

The release flow:

- tags `v1.2.3` from `trunk`
- merges `trunk` into `main`
- builds RPM + DEB packages
- copies RPM to `../ABLS-PKGS/public/rpms/<arch>/`
- copies DEB to `../ABLS-PKGS/deb-packages/<suite>/`

## Container build

```sh
podman build -t abls-agent-shelly:dev \
  --build-arg ABLS_LIBS_DEVEL_RPM_URL=<url> \
  --build-arg ABLS_AGENT_LIBS_DEVEL_RPM_URL=<url> \
  --build-arg ABLS_LIBS_RPM_URL=<url> \
  --build-arg ABLS_AGENT_LIBS_RPM_URL=<url> \
  -f Containerfile .
```
