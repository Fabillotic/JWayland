#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-server-core.h>

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_WLShmBuffer_get(JNIEnv *env, jclass clazz, jobject resource) {
	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");

	jclass WLShmBuffer_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLShmBuffer");
	jfieldID WLShmBuffer_native_ptr = (*env)->GetFieldID(env, WLShmBuffer_class, "native_ptr", "J");
	jmethodID WLShmBuffer_init = (*env)->GetMethodID(env, WLShmBuffer_class, "<init>", "()V");

	struct wl_resource *wresource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, resource, WLResource_native_ptr);
	struct wl_shm_buffer *buffer = wl_shm_buffer_get(wresource);
	if(!buffer) return NULL;

	jobject buf = (*env)->NewObject(env, WLShmBuffer_class, WLShmBuffer_init);
	(*env)->SetLongField(env, buf, WLShmBuffer_native_ptr, (jlong)(intptr_t)buffer);
	return buf;
}

JNIEXPORT jint JNICALL Java_dev_fabillo_jwayland_server_WLShmBuffer_get_1stride(JNIEnv *env, jobject obj) {
	jclass WLShmBuffer_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLShmBuffer");
	jfieldID WLShmBuffer_native_ptr = (*env)->GetFieldID(env, WLShmBuffer_class, "native_ptr", "J");

	struct wl_shm_buffer *buffer = (struct wl_shm_buffer*)(intptr_t)(*env)->GetLongField(env, obj, WLShmBuffer_native_ptr);
	return (jint) wl_shm_buffer_get_stride(buffer);
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_WLShmBuffer_get_1data(JNIEnv *env, jobject obj) {
	jclass WLShmBuffer_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLShmBuffer");
	jfieldID WLShmBuffer_native_ptr = (*env)->GetFieldID(env, WLShmBuffer_class, "native_ptr", "J");

	struct wl_shm_buffer *buffer = (struct wl_shm_buffer*)(intptr_t)(*env)->GetLongField(env, obj, WLShmBuffer_native_ptr);
	void* data = wl_shm_buffer_get_data(buffer);
	jlong capacity = (jlong) wl_shm_buffer_get_stride(buffer) * (jlong) wl_shm_buffer_get_height(buffer);
	return (*env)->NewDirectByteBuffer(env, data, capacity);
}

JNIEXPORT jint JNICALL Java_dev_fabillo_jwayland_server_WLShmBuffer_get_1format(JNIEnv *env, jobject obj) {
	jclass WLShmBuffer_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLShmBuffer");
	jfieldID WLShmBuffer_native_ptr = (*env)->GetFieldID(env, WLShmBuffer_class, "native_ptr", "J");

	struct wl_shm_buffer *buffer = (struct wl_shm_buffer*)(intptr_t)(*env)->GetLongField(env, obj, WLShmBuffer_native_ptr);
	return (jint) wl_shm_buffer_get_format(buffer);
}

JNIEXPORT jint JNICALL Java_dev_fabillo_jwayland_server_WLShmBuffer_get_1width(JNIEnv *env, jobject obj) {
	jclass WLShmBuffer_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLShmBuffer");
	jfieldID WLShmBuffer_native_ptr = (*env)->GetFieldID(env, WLShmBuffer_class, "native_ptr", "J");

	struct wl_shm_buffer *buffer = (struct wl_shm_buffer*)(intptr_t)(*env)->GetLongField(env, obj, WLShmBuffer_native_ptr);
	return (jint) wl_shm_buffer_get_width(buffer);
}

JNIEXPORT jint JNICALL Java_dev_fabillo_jwayland_server_WLShmBuffer_get_1height(JNIEnv *env, jobject obj) {
	jclass WLShmBuffer_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLShmBuffer");
	jfieldID WLShmBuffer_native_ptr = (*env)->GetFieldID(env, WLShmBuffer_class, "native_ptr", "J");

	struct wl_shm_buffer *buffer = (struct wl_shm_buffer*)(intptr_t)(*env)->GetLongField(env, obj, WLShmBuffer_native_ptr);
	return (jint) wl_shm_buffer_get_height(buffer);
}
