#!/usr/bin/env bash

cp src/* "$CEPHFS_MIMIC_REPO_ROOT/qa/libceph"
cp "$CEPHFS_MIMIC_REPO_ROOT/build/ceph.conf" "$CEPHFS_MIMIC_REPO_ROOT/qa/libceph"
cd "$CEPHFS_MIMIC_REPO_ROOT/qa/libceph"
make
