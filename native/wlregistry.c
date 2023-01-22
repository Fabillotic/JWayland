#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>
#include "interfaces.h"
#include "util.h"

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_protocol_WLRegistry_bind(JNIEnv *env, jobject obj, jint name, jstring iface, jint version) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	struct wl_proxy *wproxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	union wl_argument args[3];
	args[0].u = (uint32_t) name;
	args[1].s = (*env)->GetStringUTFChars(env, iface, NULL);
	args[2].u = (uint32_t) version;
	struct wl_proxy *nproxy = wl_proxy_marshal_array_constructor(wproxy, 0, args, &wl_callback_interface); /* TODO: Get interface from iface */
	jobject prox = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
	(*env)->SetLongField(env, prox, WLProxy_native_ptr, (jlong)(intptr_t)nproxy);
	return prox;
}

int wlregistry_dispatcher(const void *implementation, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	struct wl_proxy *proxy = (struct wl_proxy*) target;
	void* user_data = wl_proxy_get_user_data(proxy);
	JNIEnv *env = *(JNIEnv**) user_data;
	printf("REGISTRY DISPATCHER! env: %p, opcode: %d, name: '%s', signature: '%s', target: %p\n", env, opcode, msg->name, msg->signature, target);
	fflush(stdout);
	jobject listener = (jobject) implementation;

	printf("finding class...\n");
	fflush(stdout);
	jclass WLRegistryListener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/protocol/WLRegistry$WLRegistryListener");
	printf("getting opcode 0...\n");
	fflush(stdout);
	jmethodID WLRegistryListener_global = (*env)->GetMethodID(env, WLRegistryListener_class, "global", "(ILjava/lang/String;I)V");
	printf("getting opcode 1...\n");
	fflush(stdout);
	jmethodID WLRegistryListener_global_remove = (*env)->GetMethodID(env, WLRegistryListener_class, "global_remove", "(I)V");

	jvalue *values;
	char *sig;

	printf("Boutta get some arguments!\n");
	fflush(stdout);
	arguments_to_java(env, msg, args, &sig, &values);

	printf("Values: %p\n", values);
	fflush(stdout);

	switch(opcode) {
		case 0: (*env)->CallVoidMethodA(env, listener, WLRegistryListener_global, values); break;
		case 1: (*env)->CallVoidMethodA(env, listener, WLRegistryListener_global_remove, values); break;
		default:
			printf("ERROR! DISPATCHER CALLED ON INVALID OPCODE!!!!!!!\n");
			fflush(stdout);
			break;
	}

	return 0;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_protocol_WLRegistry_addListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");

	jobject listener_ref = (*env)->NewGlobalRef(env, listener);

	struct wl_proxy *proxy = (struct wl_proxy*)(intptr_t)(*env)->GetLongField(env, obj, WLProxy_native_ptr);
	JNIEnv** data = malloc(sizeof(JNIEnv*));
	*data = env;
	wl_proxy_add_dispatcher(proxy, wlregistry_dispatcher, listener_ref, data);
}
