#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_client_ClientDisplay_connect_1name(JNIEnv *env, jobject obj, jstring name) {
	jclass ClientDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/ClientDisplay");
	jfieldID ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");

	const char *name_str;
	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Display already connected!");
		return;
	}

	if(name) name_str = (*env)->GetStringUTFChars(env, name, NULL);
	else name_str = NULL;

	display = wl_display_connect(name_str);

	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Failed to connect to display!");
		return;
	}

	if(name) (*env)->ReleaseStringUTFChars(env, name, name_str);

	(*env)->SetLongField(env, obj, ClientDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_client_ClientDisplay_connect_1fd(JNIEnv *env, jobject obj, jint fd) {
	jclass ClientDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/ClientDisplay");
	jfieldID ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Display already connected!");
		return;
	}

	display = wl_display_connect_to_fd((int) fd);

	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Failed to connect to display!");
		return;
	}

	(*env)->SetLongField(env, obj, ClientDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_client_ClientDisplay_disconnect(JNIEnv *env, jobject obj) {
	jclass ClientDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/ClientDisplay");
	jfieldID ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_disconnect(display);

	(*env)->SetLongField(env, obj, ClientDisplay_native_ptr, (jlong)(intptr_t)NULL);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_client_ClientDisplay_dispatch(JNIEnv *env, jobject obj) {
	jclass ClientDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/ClientDisplay");
	jfieldID ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_dispatch(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_client_ClientDisplay_flush(JNIEnv *env, jobject obj) {
	jclass ClientDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/ClientDisplay");
	jfieldID ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_flush(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_client_ClientDisplay_roundtrip(JNIEnv *env, jobject obj) {
	jclass ClientDisplay_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/ClientDisplay");
	jfieldID ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");

	struct wl_display *display;

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		jclass IOException_class = (*env)->FindClass(env, "java/io/IOException");
		(*env)->ThrowNew(env, IOException_class, "Invalid display!");
		return;
	}

	wl_display_roundtrip(display);
}
