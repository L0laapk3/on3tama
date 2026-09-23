**installing bazelisk & buildifier (lazy)**
`pnpm i -g @bazel/bazelisk @bazel/buildifier-linux_x64`

# Run
`bazel run //on3tama`

# Run debug build
`bazel run --config=dbg //on3tama`

# Update compdb
`bazel run //:compdb`