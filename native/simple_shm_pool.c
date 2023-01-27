#include <stdint.h>
#include <unistd.h>
#include <jni.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>

void randname(char *buf) {
	struct timespec ts;
	int i;
	long r;

	clock_gettime(CLOCK_REALTIME, &ts);
	r = ts.tv_nsec;
	for(i = 0; i < 6; i++) {
		buf[i] = 'A' + (r & 15) + (r & 16) * 2;
		r >>= 5;
	}
}

int create_shm_file() {
	int fd, retries;

	retries = 100;
	do {
		char name[] = "/wl_shm-XXXXXX";
		randname(name + sizeof(name) - 7);
		--retries;
		fd = shm_open(name, O_RDWR | O_CREAT | O_EXCL, 0600);
		if(fd >= 0) {
			shm_unlink(name);
			return fd;
		}
	} while(retries > 0 && errno == EEXIST);
	return -1;
}

int allocate_shm_file(size_t size) {
	int fd, ret;

	fd = create_shm_file();
	if(fd < 0) return -1;

	do {
		ret = ftruncate(fd, size);
	} while(ret < 0 && errno == EINTR);
	if(ret < 0) {
		close(fd);
		return -1;
	}
	return fd;
}

JNIEXPORT jint JNICALL Java_dev_fabillo_jwayland_SimpleShmPool_allocate_1shm_1file(JNIEnv *env, jclass clazz, jint size) {
	return allocate_shm_file(size);
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_SimpleShmPool_map_1shm(JNIEnv *env, jclass clazz, jint fd, jint size) {
	void *data;

	data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(data == MAP_FAILED) {
		close(fd);
		return NULL;
	}
	return (*env)->NewDirectByteBuffer(env, data, size);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_SimpleShmPool_unmap_1shm(JNIEnv *env, jclass clazz, jobject buffer) {
	void *data;
	int size;

	data = (*env)->GetDirectBufferAddress(env, buffer);
	size = (*env)->GetDirectBufferCapacity(env, buffer);

	munmap(data, size);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_SimpleShmPool_close_1shm_1fd(JNIEnv *env, jclass clazz, jint fd) {
	close(fd);
}
