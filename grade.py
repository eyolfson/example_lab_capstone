#!/usr/bin/env python3

import json
import pathlib
import shutil
import subprocess

wut_dir = pathlib.Path(__file__).resolve().parent
build_dir = wut_dir.joinpath('build')

shutil.rmtree(build_dir, ignore_errors=True)

subprocess.run(
    ['meson', 'setup', 'build'],
    check=True,
    cwd=wut_dir,
    stdout=subprocess.DEVNULL
)

subprocess.run(
    ['meson', 'test', '-C', 'build'],
    cwd=wut_dir,
    stdout=subprocess.DEVNULL
)

testlog_path = build_dir.joinpath('meson-logs/testlog.json')
if not testlog_path.exists():
    print("failed to run tests (code doesn't compile?)")
    exit(1)

passed = 0
total = 0
with open(testlog_path, 'r') as f:
    for line in f:
        test = json.loads(line)
        if test['result'] == 'OK':
            passed += 1
        total += 1
print(f'{passed}/{total} passed (grade not finalized)')
