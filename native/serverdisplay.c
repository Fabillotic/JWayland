#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <wayland-server-core.h>
#include "util.h"
#include "interfaces.h"

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_create_1native(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display = wl_display_create();
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Failed to create display!");
	}
	(*env)->SetLongField(env, obj, ServerDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_run(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_run(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_terminate(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_terminate(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_flush_1clients(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_flush_clients(display);
}

JNIEXPORT jstring JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1socket_1auto(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return NULL;
	}

	return (*env)->NewStringUTF(env, wl_display_add_socket_auto(display));
}

JNIEXPORT jboolean JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1socket_1fd(JNIEnv *env, jobject obj, jint fd) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return JNI_FALSE;
	}

	return wl_display_add_socket_fd(display, (int) fd) == 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1socket(JNIEnv *env, jobject obj, jstring name) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return JNI_FALSE;
	}

	return wl_display_add_socket(display, (*env)->GetStringUTFChars(env, name, NULL)) == 0 ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_destroy_1clients(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_destroy_clients(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_destroy(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_destroy(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_init_1shm(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_init_shm(display);
}

struct global_data {
	JNIEnv *env;
	jobject listener;
};

void global_bind(struct wl_client *client, void *data, uint32_t version, uint32_t id) {
	struct global_data *d = (struct global_data*) data;
	JNIEnv *env = d->env;

	jclass WLGlobalBindListener_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLGlobal$WLGlobalBindListener");
	jmethodID WLGlobalBindListener_bind = (*env)->GetMethodID(env, WLGlobalBindListener_class, "bind", "(Ldev/fabillo/jwayland/server/WLClient;II)V");
	jclass WLClient_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*env)->GetFieldID(env, WLClient_class, "native_ptr", "J");
	jmethodID WLClient_init = (*env)->GetMethodID(env, WLClient_class, "<init>", "()V");

	jobject c = (*env)->NewObject(env, WLClient_class, WLClient_init);
	(*env)->SetLongField(env, c, WLClient_native_ptr, (jlong)(intptr_t)client);
	(*env)->CallVoidMethod(env, d->listener, WLGlobalBindListener_bind, c, (jint)version, (jint)id);
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_create_1global(JNIEnv *env, jobject obj, jstring interface_name, jint version, jobject listener) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");
	jclass WLGlobal_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLGlobal");
	jfieldID WLGlobal_native_ptr = (*env)->GetFieldID(env, WLGlobal_class, "native_ptr", "J");
	jmethodID WLGlobal_init = (*env)->GetMethodID(env, WLGlobal_class, "<init>", "()V");

	struct wl_display *display;
	struct global_data *data;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return NULL;
	}
	jobject listener_ref = (*env)->NewGlobalRef(env, listener);
	data = malloc(sizeof(struct global_data));
	data->env = env;
	data->listener = listener_ref;

	struct wl_global *glob = wl_global_create(display, get_interface_by_name((*env)->GetStringUTFChars(env, interface_name, NULL)), (int) version, data, global_bind);
	if(!glob) return NULL;

	jobject global = (*env)->NewObject(env, WLGlobal_class, WLGlobal_init);
	(*env)->SetLongField(env, global, WLGlobal_native_ptr, (jlong)(intptr_t)glob);
	return global;
}

int default_dispatcher(const void *user_data, void *target, uint32_t opcode, const struct wl_message *msg, union wl_argument *args) {
	return 0;
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_create_1resource(JNIEnv *env, jobject obj, jobject client, jstring interface_name, jint version, jint id) {
	jclass WLClient_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*env)->GetFieldID(env, WLClient_class, "native_ptr", "J");

	char c[200];
	c[0] = 0;
	strcat(c, "dev/fabillo/jwayland/protocol/server/");
	get_camel_name(c + strlen(c), (*env)->GetStringUTFChars(env, interface_name, NULL));
	strcat(c, "Resource");

	jclass InterfaceResource_class = (*env)->FindClass(env, c);
	jfieldID InterfaceResource_native_ptr = (*env)->GetFieldID(env, InterfaceResource_class, "native_ptr", "J");
	jmethodID InterfaceResource_init = (*env)->GetMethodID(env, InterfaceResource_class, "<init>", "()V");

	struct wl_client *cl = (struct wl_client*)(intptr_t)(*env)->GetLongField(env, client, WLClient_native_ptr);

	const struct wl_interface *inf = get_interface_by_name((*env)->GetStringUTFChars(env, interface_name, NULL));
	if(!inf) return NULL;

	struct wl_resource *r = wl_resource_create(cl, inf, (int) version, (uint32_t) id);
	if(!r) return NULL;

	wl_resource_set_dispatcher(r, default_dispatcher, NULL, NULL, NULL);

	jobject resource = (*env)->NewObject(env, InterfaceResource_class, InterfaceResource_init);
	(*env)->SetLongField(env, resource, InterfaceResource_native_ptr, (jlong)(intptr_t)r);
	return resource;
}

JNIEXPORT jobject JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_get_1event_1loop(JNIEnv *env, jobject obj) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");
	jclass WLEventLoop_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLEventLoop");
	jfieldID WLEventLoop_native_ptr = (*env)->GetFieldID(env, WLEventLoop_class, "native_ptr", "J");
	jmethodID WLEventLoop_init = (*env)->GetMethodID(env, WLEventLoop_class, "<init>", "()V");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return NULL;
	}
	struct wl_event_loop *wloop = wl_display_get_event_loop(display);

	jobject loop = (*env)->NewObject(env, WLEventLoop_class, WLEventLoop_init);
	(*env)->SetLongField(env, loop, WLEventLoop_native_ptr, (jlong)(intptr_t)wloop);
	return loop;
}

jobject client_created_listener_obj = NULL;
JNIEnv *j_env;

void on_client_create(struct wl_listener *listener, void *data) {
	jclass WLClientCreatedListener_class = (*j_env)->FindClass(j_env, "dev/fabillo/jwayland/server/WLClient$WLClientCreatedListener");
	jmethodID WLClientCreatedListener_client_created = (*j_env)->GetMethodID(j_env, WLClientCreatedListener_class, "client_created", "(Ldev/fabillo/jwayland/server/WLClient;)V");
	jclass WLClient_class = (*j_env)->FindClass(j_env, "dev/fabillo/jwayland/server/WLClient");
	jfieldID WLClient_native_ptr = (*j_env)->GetFieldID(j_env, WLClient_class, "native_ptr", "J");
	jmethodID WLClient_init = (*j_env)->GetMethodID(j_env, WLClient_class, "<init>", "()V");

	if(!client_created_listener_obj) {
		jclass IOException_class = (*j_env)->FindClass(j_env, "java/io/IOException");
		(*j_env)->ThrowNew(j_env, IOException_class, "Listener engaged even though no listener object is present!");
		return;
	}

	jobject client = (*j_env)->NewObject(j_env, WLClient_class, WLClient_init);
	(*j_env)->SetLongField(j_env, client, WLClient_native_ptr, (jlong)(intptr_t)data);
	(*j_env)->CallVoidMethod(j_env, client_created_listener_obj, WLClientCreatedListener_client_created, client);
}

struct wl_listener client_created_listener = {
	.notify = on_client_create
};

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_server_ServerDisplay_add_1client_1created_1listener(JNIEnv *env, jobject obj, jobject listener) {
	jclass ServerDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/ServerDisplay");
	jfieldID ServerDisplay_native_ptr = (*env)->GetFieldID(env, ServerDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ServerDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	if(client_created_listener_obj) {
		jclass IllegalStateException_class = (*env)->FindClass(env, "java/lang/IllegalStateException");
		(*env)->ThrowNew(env, IllegalStateException_class, "Client creation listener already registered!");
		return;
	}

	j_env = env;
	wl_display_add_client_created_listener(display, &client_created_listener);
	client_created_listener_obj = (*env)->NewGlobalRef(env, listener);
}
