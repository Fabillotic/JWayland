#include <jni.h>
#include <stdio.h>
#include <stdint.h>
#include <wayland-client-core.h>

jclass ClientDisplay_class;
jfieldID ClientDisplay_native_ptr;

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_init_1jni(JNIEnv *env, jclass clazz) {
	ClientDisplay_class = clazz;
	ClientDisplay_native_ptr = (*env)->GetFieldID(env, ClientDisplay_class, "native_ptr", "J");
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_connect_1name(JNIEnv *env, jobject obj, jstring name) {
	const char *name_str;
	struct wl_display *display;

	printf("CONNECT!\n");
	fflush(stdout);

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(display) {
		printf("DISPLAY ALREADY CONNECTED!\n");
		fflush(stdout);
		return;
	}

	if(name) name_str = (*env)->GetStringUTFChars(env, name, NULL);
	else name_str = NULL;

	display = wl_display_connect(name_str);

	if(name) (*env)->ReleaseStringUTFChars(env, name, name_str);

	(*env)->SetLongField(env, obj, ClientDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_connect_1fd(JNIEnv *env, jobject obj, jint fd) {
	struct wl_display *display;

	printf("CONNECT!\n");
	fflush(stdout);

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(display) {
		printf("DISPLAY ALREADY CONNECTED!\n");
		fflush(stdout);
		return;
	}

	display = wl_display_connect_to_fd((int) fd);

	(*env)->SetLongField(env, obj, ClientDisplay_native_ptr, (jlong)(intptr_t)display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_disconnect(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	printf("DISCONNECT!\n");
	fflush(stdout);

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY IS NOT CONNECTED!\n");
		fflush(stdout);
		return;
	}

	wl_display_disconnect(display);

	(*env)->SetLongField(env, obj, ClientDisplay_native_ptr, (jlong)(intptr_t)NULL);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_dispatch(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	printf("DISPATCH!\n");
	fflush(stdout);

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY IS NOT CONNECTED!\n");
		fflush(stdout);
		return;
	}

	wl_display_dispatch(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_flush(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	printf("FLUSH!\n");
	fflush(stdout);

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY IS NOT CONNECTED!\n");
		fflush(stdout);
		return;
	}

	wl_display_flush(display);
}

JNIEXPORT void JNICALL Java_dev_fabillo_jwayland_ClientDisplay_roundtrip(JNIEnv *env, jobject obj) {
	struct wl_display *display;

	printf("ROUNDTRIP!\n");
	fflush(stdout);

	display = (struct wl_display*)(intptr_t)(*env)->GetLongField(env, obj, ClientDisplay_native_ptr);
	if(!display) {
		printf("DISPLAY IS NOT CONNECTED!\n");
		fflush(stdout);
		return;
	}

	wl_display_roundtrip(display);
}
