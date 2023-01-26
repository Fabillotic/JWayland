#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WLShmPool_create_1buffer(JNIEnv *env, jobject obj, jint offset, jint width, jint height, jint stride, jint format) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	const struct wl_interface *inf = get_interface_by_name("wl_buffer");
	if(!inf) return NULL;
	struct wl_proxy *nproxy = wl_proxy_marshal_constructor(wproxy, 0, inf, (uint32_t) 0, (int32_t) offset, (int32_t) width, (int32_t) height, (int32_t) stride, (uint32_t) format);
	if(!nproxy) return NULL;
	jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
	(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
	return prox;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShmPool_destroy(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 1);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShmPool_resize(JNIEnv *env, jobject obj, jint size) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 2, (int32_t) size);
}

int wl_shm_pool_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLShmPool$WLShmPoolListener");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLShmPool_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_shm_pool_dispatcher, listener_ref, data);
}
