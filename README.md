# libcephfs-tests - tests using the cephfs library

In order to run these tests you must:

1. Have a built [ceph](https://github.com/ceph/ceph) repository currently on the `mimic` branch, and a ceph cluster is currently running
2. Modify, and export the following environment variables:
```shell
export CEPHFS_MIMIC_REPO_ROOT="/path/to/ceph/root"
export PYTHONPATH="./pybind:${CEPHFS_MIMIC_REPO_ROOT}/src/pybind:${CEPHFS_MIMIC_REPO_ROOT}/build/lib/cython_modules/lib.2:"
export LD_LIBRARY_PATH="${CEPHFS_MIMIC_REPO_ROOT}/build/lib"

```
3. And finally, while in the terminal, `cd` into the root of this repository and run the `copy_and_compile.sh` script which will copy the tests and compile them if needed.
4. In the terminal now execute:
```shell
cd "$CEPHFS_MIMIC_REPO_ROOT"/qa/libceph

```
5. And finally, run the C tests:

```shell
./write ceph.conf dummy_file
./read ceph.conf dummy_file
```

or run the Python 2 tests:

```shell
./write.py  # writes dummy_file
./read.py   # reads dummy_file
```
