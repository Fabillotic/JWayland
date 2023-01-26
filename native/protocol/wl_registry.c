#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WLRegistry_bind(JNIEnv *env, jobject obj, jint name, jstring interface_name, jint interface_version) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	const struct wl_interface *inf = get_interface_by_name((*env)->GetStringUTFChars(env, interface_name, NULL));
	if(!inf) return NULL;
	struct wl_proxy *nproxy = wl_proxy_marshal_constructor(wproxy, 0, inf, (uint32_t) name, (*env)->GetStringUTFChars(env, interface_name, NULL), (uint32_t) interface_version, (uint32_t) 0);
	if(!nproxy) return NULL;
	jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
	(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
	return prox;
}

int wl_registry_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	jobject listener = (jobject) implementation;

	jclass listener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLRegistry$WLRegistryListener");
	jmethodID mListener_global = (*env)->GetMethodID(env, listener_class, "global", "(ILjava/lang/String;I)V");
	jmethodID mListener_global_remove = (*env)->GetMethodID(env, listener_class, "global_remove", "(I)V");

	jvalue *values;
	char *sig;

	arguments_to_java(env, msg, args, &sig, &values);
	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, mListener_global, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, mListener_global_remove, values); break;
		default: break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLRegistry_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv **data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(wproxy, wl_registry_dispatcher, listener_ref, data);
}
