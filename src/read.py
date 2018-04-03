#!/usr/bin/env python2

import cephfs
import sys
import os
import hashlib

config_file = "ceph.conf"

cephfs_handle = cephfs.LibCephFS()

cephfs_handle.create() # create 
cephfs_handle.conf_read_file(config_file)
cephfs_handle.conf_parse_argv(sys.argv)
cephfs_handle.mount()
cephfs_handle.chdir("/")

# Note: there's no chmod function

file_descriptor = -1;
text_to_write = "123pescao"

file_descriptor = cephfs_handle.open("dummy_file", os.O_RDONLY) # this os.FLAG is VERY IMPORTANT!
print "File descriptor is: ", file_descriptor
#cephfs_handle.write(file_descriptor,cephfs.cstr(len(text_to_write) * 8, str("hola")),0);
return_buffer = cephfs_handle.read(file_descriptor,0,4028)

print "size read: ", len(return_buffer)
print "contents of file: ", return_buffer

hash_sum = hashlib.sha1()
hash_sum.update(return_buffer)

print "Sha1 sum: ", hash_sum.hexdigest()

#cephfs_handle.fsync(file_descriptor,0);


