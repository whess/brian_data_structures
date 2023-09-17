workspace(name = "brian_data_structures")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# bazel/autocomplete helper
http_archive(
    name = "hedron_compile_commands",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/b33a4b05c2287372c8e932c55ff4d3a37e6761ed.tar.gz",
    strip_prefix = "bazel-compile-commands-extractor-b33a4b05c2287372c8e932c55ff4d3a37e6761ed",
    sha256 = "99bc3106eb6ce5ffab3c31de8501d4d628de5f1acd74b8b563a876bd39a2e32f",
)
load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")
hedron_compile_commands_setup()

# absl
http_archive(
   name = "absl",
   sha256 = "51d676b6846440210da48899e4df618a357e6e44ecde7106f1e44ea16ae8adc7",
   strip_prefix = "abseil-cpp-20230125.3",
   urls = ["https://github.com/abseil/abseil-cpp/archive/refs/tags/20230125.3.zip"],
)

# Copied deps from absl:

# Bazel Skylib.
http_archive(
    name = "bazel_skylib",  # 2022-11-16T18:29:32Z
    sha256 = "a22290c26d29d3ecca286466f7f295ac6cbe32c0a9da3a91176a90e0725e3649",
    strip_prefix = "bazel-skylib-5bfcb1a684550626ce138fe0fe8f5f702b3764c3",
    urls = ["https://github.com/bazelbuild/bazel-skylib/archive/5bfcb1a684550626ce138fe0fe8f5f702b3764c3.zip"],
)

# GoogleTest/GoogleMock framework. Used by most unit-tests.
http_archive(
    name = "com_google_googletest",  # 2023-02-28T13:15:29Z
    sha256 = "82ad62a4e26c199de52a707778334e80f6b195dd298d48d520d8507d2bcb88c4",
    strip_prefix = "googletest-2d4f208765af7fa376b878860a7677ecc0bc390a",
    # Keep this URL in sync with ABSL_GOOGLETEST_COMMIT in ci/cmake_common.sh.
    urls = ["https://github.com/google/googletest/archive/2d4f208765af7fa376b878860a7677ecc0bc390a.zip"],
)

# RE2 (the regular expression library used by GoogleTest)
# Note this must use a commit from the `abseil` branch of the RE2 project.
# https://github.com/google/re2/tree/abseil
http_archive(
    name = "com_googlesource_code_re2",
    sha256 = "0a890c2aa0bb05b2ce906a15efb520d0f5ad4c7d37b8db959c43772802991887",
    strip_prefix = "re2-a427f10b9fb4622dd6d8643032600aa1b50fbd12",
    urls = ["https://github.com/google/re2/archive/a427f10b9fb4622dd6d8643032600aa1b50fbd12.zip"],  # 2022-06-09
)

# Google benchmark.
http_archive(
    name = "com_github_google_benchmark",  # 2023-01-10T16:48:17Z
    sha256 = "ede6830512f21490eeea1f238f083702eb178890820c14451c1c3d69fd375b19",
    strip_prefix = "benchmark-a3235d7b69c84e8c9ff8722a22b8ac5e1bc716a6",
    urls = ["https://github.com/google/benchmark/archive/a3235d7b69c84e8c9ff8722a22b8ac5e1bc716a6.zip"],
)

# Bazel platform rules.
http_archive(
    name = "platforms",  # 2022-11-09T19:18:22Z
    sha256 = "b4a3b45dc4202e2b3e34e3bc49d2b5b37295fc23ea58d88fb9e01f3642ad9b55",
    strip_prefix = "platforms-3fbc687756043fb58a407c2ea8c944bc2fe1d922",
    urls = ["https://github.com/bazelbuild/platforms/archive/3fbc687756043fb58a407c2ea8c944bc2fe1d922.zip"],
)

