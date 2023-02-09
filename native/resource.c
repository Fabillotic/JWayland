#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wayland-server-core.h>

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_WLResource_get_1client(JNIEnv *env, jobject obj) {
	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");
	jclass WLClient_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*env)->GetFieldID(env, WLClient_class, "native_ptr", "J");
	jmethodID WLClient_init = (*env)->GetMethodID(env, WLClient_class, "<init>", "()V");

	struct wl_resource *resource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, obj, WLResource_native_ptr);

	struct wl_client *c = wl_resource_get_client(resource);

	jobject client = (*env)->NewObject(env, WLClient_class, WLClient_init);
	(*env)->SetLongField(env, client, WLClient_native_ptr, (jlong)(intptr_t)c);
	return client;
}

struct listener_data {
	struct wl_listener w_listen;
	JNIEnv *env;
	jobject listener;
};

void destroy_resource(struct wl_listener *l, void *data) {
	struct listener_data *d = (struct listener_data*) l;

	JNIEnv *env = d->env;
	jobject listener = d->listener;

	free(d);

	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");
	jmethodID WLResource_init = (*env)->GetMethodID(env, WLResource_class, "<init>", "()V");
	jclass WLResourceDestroyedListener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource$WLResourceDestroyedListener");
	jmethodID WLResourceDestroyedListener_resource_destroyed = (*env)->GetMethodID(env, WLResourceDestroyedListener_class, "resource_destroyed", "(Ldev/fabillo/jwayland/server/WLResource;)V");

	jobject resource = (*env)->NewObject(env, WLResource_class, WLResource_init);
	(*env)->SetLongField(env, resource, WLResource_native_ptr, (jlong)(intptr_t)data);
	(*env)->CallVoidMethod(env, listener, WLResourceDestroyedListener_resource_destroyed, resource);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_WLResource_addDestroyListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");

	struct wl_resource *resource = (struct wl_resource*)(intptr_t)(*env)->GetLongField(env, obj, WLResource_native_ptr);

	struct listener_data *d = malloc(sizeof(struct listener_data));
	d->w_listen.notify = destroy_resource;
	d->env = env;
	d->listener = (*env)->NewGlobalRef(env, listener);

	wl_resource_add_destroy_listener(resource, (struct wl_listener*) d);
}
