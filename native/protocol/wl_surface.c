#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_destroy(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 0);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_attach(JNIEnv *env, jobject obj, jobject buffer, jint x, jint y) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 1, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, buffer, WLProxy_native_ptr), (int32_t) x, (int32_t) y);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_damage(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 2, (int32_t) x, (int32_t) y, (int32_t) width, (int32_t) height);
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_frame(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	const struct wl_interface *inf = get_interface_by_name("wl_callback");
	if(!inf) return NULL;
	struct wl_proxy *nproxy = wl_proxy_marshal_constructor(wproxy, 3, inf, (uint32_t) 0);
	if(!nproxy) return NULL;
	jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
	(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
	return prox;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_set_1opaque_1region(JNIEnv *env, jobject obj, jobject region) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 4, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, region, WLProxy_native_ptr));
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_set_1input_1region(JNIEnv *env, jobject obj, jobject region) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 5, (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, region, WLProxy_native_ptr));
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_commit(JNIEnv *env, jobject obj) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 6);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_set_1buffer_1transform(JNIEnv *env, jobject obj, jint transform) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 7, (int32_t) transform);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_set_1buffer_1scale(JNIEnv *env, jobject obj, jint scale) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 8, (int32_t) scale);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_damage_1buffer(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 9, (int32_t) x, (int32_t) y, (int32_t) width, (int32_t) height);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_offset(JNIEnv *env, jobject obj, jint x, jint y) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	wl_proxy_marshal(wproxy, 10, (int32_t) x, (int32_t) y);
}

int wl_surface_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLSurface$WLSurfaceListener");
	jmethodID mListener_enter = (*env)->GetMethodID(env, listener_class, "enter", "(Ldev/fabillo/jwayland/WLProxy;)V");
	jmethodID mListener_leave = (*env)->GetMethodID(env, listener_class, "leave", "(Ldev/fabillo/jwayland/WLProxy;)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_enter, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_leave, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLSurface_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_surface_dispatcher, listener_ref, data);
}
