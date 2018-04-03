#!/usr/bin/env python2

import cephfs
import sys
import os
import hashlib

config_file = "ceph.conf"

cephfs_handle = cephfs.LibCephFS()

cephfs_handle.create()
cephfs_handle.conf_read_file(config_file)
cephfs_handle.conf_parse_argv(sys.argv)
cephfs_handle.mount()
cephfs_handle.chdir("/")

# Note: there's no chmod function

file_descriptor = -1;
text_to_write = "123pescao"

# the errors are handled internaly in the python bindings. no need to handle them here.
# we can just print stuff to take a look the values

file_descriptor = cephfs_handle.open("dummy_file", os.O_CREAT | os.O_TRUNC | os.O_WRONLY) # this os.FLAG is VERY IMPORTANT!
print "File descriptor is: ", file_descriptor

bytes_written = cephfs_handle.write(file_descriptor, text_to_write, 0);
print "wrote ", bytes_written, " bytes"

cephfs_handle.fsync(file_descriptor,0); # make sure we flush to disk
