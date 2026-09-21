# Lazy bazelisk install from pnpm
`pnpm install -g @bazel/bazelisk`

# Run
`bazel run //on3tama`

# Run debug build
`bazel run --config=dbg //on3tama`

# Update compdb
`bazel run //:compdb`