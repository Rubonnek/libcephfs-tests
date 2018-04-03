CFLAGS = -Wall -Wextra -D_GNU_SOURCE  -lcrypto -lcephfs -L$(CEPHFS_MIMIC_REPO_ROOT)/build/lib -I$(CEPHFS_MIMIC_REPO_ROOT)/src/googletest/googletest/include/

TARGETS = read write

.c:
	$(CXX) $(CFLAGS) $@.c -o $@

all:	$(TARGETS)

clean:
	rm $(TARGETS)
