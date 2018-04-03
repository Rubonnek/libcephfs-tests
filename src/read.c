#define _FILE_OFFSET_BITS 64
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include "../../src/include/cephfs/libcephfs.h"
#include <openssl/sha.h>

int main(int argc, const char **argv)
{
        struct ceph_mount_info *cmount;
        int ret, fd, len;
        char buf[5024];

        if (argc < 3) {
                fprintf(stderr, "usage: ./%s <conf> <file>\n", argv[0]);
                exit(1);
        }

        ret = ceph_create(&cmount, NULL);
        if (ret) {
                fprintf(stderr, "ceph_create=%d\n", ret);
                exit(1);
        }

        ret = ceph_conf_read_file(cmount, argv[1]);
        if (ret) {
                fprintf(stderr, "ceph_conf_read_file=%d\n", ret);
                exit(1);
        }

        ret = ceph_conf_parse_argv(cmount, argc, argv);
        if (ret) {
                fprintf(stderr, "ceph_conf_parse_argv=%d\n", ret);
                exit(1);
        }

        ret = ceph_mount(cmount, "/");
        if (ret) {
                fprintf(stderr, "ceph_mount=%d\n", ret);
                exit(1);
        }

        ret = ceph_chdir(cmount, "/");
        if (ret) {
                fprintf(stderr, "ceph_chdir=%d\n", ret);
                exit(1);
        }

        fd = ceph_open(cmount, argv[2], O_RDONLY, 0777); 
        if (fd < 0) {
                fprintf(stderr, "ceph_open=%d\n", fd);
                exit(1);
        }

        len = ceph_read(cmount, fd, buf, sizeof(buf), 0);
        fprintf(stdout, "read %d bytes\n", len);

		// Lets write the file to disk just so I can run sha1sum against it
		FILE *file_descriptor = fopen("extracted_test_from_cephfs.txt", "w");
		if ( file_descriptor == NULL )
		{
			printf("ERROR OPENING THE FILE!");
        	ceph_shutdown(cmount);
			return -10;
		}
		fwrite(buf,len,1,file_descriptor);
		fclose(file_descriptor);

		printf("Here's what we read from CephFS:\n%s\n\n", buf);

		// The data to be hashed is in buf
		unsigned char hash[SHA_DIGEST_LENGTH];
		SHA1((const unsigned char*)buf, len, hash); // I think this const unsigned char* casting may be the reason why the hash differs, but I honestly don't know.

		// hash now contains the 20-byte SHA-1 hash
		printf("Here's the sha1sum hash of the file:\n");
		int i = SHA_DIGEST_LENGTH; 
		while (i >= 0) 
		{
			fprintf (stdout, "%02x",hash[i]); 
			--i;
		}
		printf("\n");

        ceph_shutdown(cmount);

        return 0;
}
