#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wayland-server-core.h>

struct listener_data {
	struct wl_listener w_listen;
	JNIEnv *env;
	jobject listener;
};

void destroy_client(struct wl_listener *l, void *data) {
	struct listener_data *d = (struct listener_data*) l;

	JNIEnv *env = d->env;
	jobject listener = d->listener;

	free(d);

	jclass WLClient_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*env)->GetFieldID(env, WLClient_class, "native_ptr", "J");
	jmethodID WLClient_init = (*env)->GetMethodID(env, WLClient_class, "<init>", "()V");
	jclass WLClientDestroyedListener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient$WLClientDestroyedListener");
	jmethodID WLClientDestroyedListener_client_destroyed = (*env)->GetMethodID(env, WLClientDestroyedListener_class, "client_destroyed", "(Ldev/fabillo/jwayland/server/WLClient;)V");

	jobject client = (*env)->NewObject(env, WLClient_class, WLClient_init);
	(*env)->SetLongField(env, client, WLClient_native_ptr, (jlong)(intptr_t)data);
	(*env)->CallVoidMethod(env, listener, WLClientDestroyedListener_client_destroyed, client);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_WLClient_addDestroyListener(JNIEnv *env, jobject obj, jobject listener) {
	jclass WLClient_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*env)->GetFieldID(env, WLClient_class, "native_ptr", "J");

	struct wl_client *client = (struct wl_client*)(intptr_t)(*env)->GetLongField(env, obj, WLClient_native_ptr);

	struct listener_data *d = malloc(sizeof(struct listener_data));
	d->w_listen.notify = destroy_client;
	d->env = env;
	d->listener = (*env)->NewGlobalRef(env, listener);

	wl_client_add_destroy_listener(client, (struct wl_listener*) d);
}
