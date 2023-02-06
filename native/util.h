#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static inline void arguments_to_java_client(JNIEnv *env, void *proxy, const char* proxy_clazzname, const struct wl_message *msg, union wl_argument *args, char **r_sig, jvalue **r_values) {
	int i, n;
	char c;
	char *sig;
	jvalue *values;

	jclass WLProxy_class = (*env)->FindClass(env, "dev/fabillo/jwayland/client/WLProxy");
	jfieldID WLProxy_native_ptr = (*env)->GetFieldID(env, WLProxy_class, "native_ptr", "J");
	jmethodID WLProxy_init = (*env)->GetMethodID(env, WLProxy_class, "<init>", "()V");
	jclass WLTheProxy_class = (*env)->FindClass(env, proxy_clazzname);
	jfieldID WLTheProxy_native_ptr = (*env)->GetFieldID(env, WLTheProxy_class, "native_ptr", "J");
	jmethodID WLTheProxy_init = (*env)->GetMethodID(env, WLTheProxy_class, "<init>", "()V");
	jclass WLFixed_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLFixed");
	jfieldID WLFixed_data = (*env)->GetFieldID(env, WLFixed_class, "data", "I");
	jmethodID WLFixed_init = (*env)->GetMethodID(env, WLFixed_class, "<init>", "()V");

	sig = malloc(200);
	sig[0] = '\0';
	strcat(sig, "L");
	strcat(sig, proxy_clazzname);
	strcat(sig, ";");
	n = 1;
	for(i = 0; (c = msg->signature[i]) != '\0'; i++) {
		if(c >= '0' && c <= '9') continue;
		else if(c == '?') continue;
		else if(c == 'i' || c == 'u' || c == 'h' || c == 'n') {
			strcat(sig, "I");
			n++;
		}
		else if(c == 's') {
			strcat(sig, "Ljava/lang/String;");
			n++;
		}
		else if(c == 'o') {
			strcat(sig, "Ldev/fabillo/jwayland/client/WLProxy;");
			n++;
		}
		else if(c == 'f') {
			strcat(sig, "Ldev/fabillo/jwayland/WLFixed;");
			n++;
		}
		else if(c == 'a') {
			/* TODO: Not yet supported */
		}
	}
	values = malloc(sizeof(jvalue) * n);
	values[0].l = (*env)->NewObject(env, WLTheProxy_class, WLTheProxy_init);
	(*env)->SetLongField(env, values[0].l, WLTheProxy_native_ptr, (jlong)(intptr_t)proxy);
	n = 1;
	for(i = 0; (c = msg->signature[i]) != '\0'; i++) {
		if(c >= '0' && c <= '9') continue;
		else if(c == '?') continue;
		else if(c == 'i' || c == 'u' || c == 'h' || c == 'n') {
			values[n].i = (jint) args[n-1].i;
			n++;
		}
		else if(c == 's') {
			values[n].l = (jobject) (*env)->NewStringUTF(env, args[n-1].s);
			n++;
		}
		else if(c == 'o') {
			values[n].l = (*env)->NewObject(env, WLProxy_class, WLProxy_init);
			(*env)->SetLongField(env, values[n].l, WLProxy_native_ptr, (jlong)(intptr_t)args[n-1].o);
			n++;
		}
		else if(c == 'f') {
			values[n].l = (*env)->NewObject(env, WLFixed_class, WLFixed_init);
			(*env)->SetIntField(env, values[n].l, WLFixed_data, args[n-1].i);
			n++;
		}
	}
	*r_values = values;
	*r_sig = sig;
}

static inline void arguments_to_java_server(JNIEnv *env, void *resource, const char* resource_clazzname, const struct wl_message *msg, union wl_argument *args, char **r_sig, jvalue **r_values) {
	int i, n;
	char c;
	char *sig;
	jvalue *values;

	jclass WLResource_class = (*env)->FindClass(env, "dev/fabillo/jwayland/server/WLResource");
	jfieldID WLResource_native_ptr = (*env)->GetFieldID(env, WLResource_class, "native_ptr", "J");
	jmethodID WLResource_init = (*env)->GetMethodID(env, WLResource_class, "<init>", "()V");
	jclass WLTheResource_class = (*env)->FindClass(env, resource_clazzname);
	jfieldID WLTheResource_native_ptr = (*env)->GetFieldID(env, WLTheResource_class, "native_ptr", "J");
	jmethodID WLTheResource_init = (*env)->GetMethodID(env, WLTheResource_class, "<init>", "()V");
	jclass WLFixed_class = (*env)->FindClass(env, "dev/fabillo/jwayland/WLFixed");
	jfieldID WLFixed_data = (*env)->GetFieldID(env, WLFixed_class, "data", "I");
	jmethodID WLFixed_init = (*env)->GetMethodID(env, WLFixed_class, "<init>", "()V");

	sig = malloc(200);
	sig[0] = '\0';
	strcat(sig, "L");
	strcat(sig, resource_clazzname);
	strcat(sig, ";");
	n = 1;
	for(i = 0; (c = msg->signature[i]) != '\0'; i++) {
		if(c >= '0' && c <= '9') continue;
		else if(c == '?') continue;
		else if(c == 'i' || c == 'u' || c == 'h' || c == 'n') {
			strcat(sig, "I");
			n++;
		}
		else if(c == 's') {
			strcat(sig, "Ljava/lang/String;");
			n++;
		}
		else if(c == 'o') {
			strcat(sig, "Ldev/fabillo/jwayland/server/WLResource;");
			n++;
		}
		else if(c == 'f') {
			strcat(sig, "Ldev/fabillo/jwayland/WLFixed;");
			n++;
		}
		else if(c == 'a') {
			/* TODO: Not yet supported */
		}
	}
	values = malloc(sizeof(jvalue) * n);
	values[0].l = (*env)->NewObject(env, WLTheResource_class, WLTheResource_init);
	(*env)->SetLongField(env, values[0].l, WLTheResource_native_ptr, (jlong)(intptr_t)resource);
	n = 1;
	for(i = 0; (c = msg->signature[i]) != '\0'; i++) {
		if(c >= '0' && c <= '9') continue;
		else if(c == '?') continue;
		else if(c == 'i' || c == 'u' || c == 'h' || c == 'n') {
			values[n].i = (jint) args[n-1].i;
			n++;
		}
		else if(c == 's') {
			values[n].l = (jobject) (*env)->NewStringUTF(env, args[n-1].s);
			n++;
		}
		else if(c == 'o') {
			values[n].l = (*env)->NewObject(env, WLResource_class, WLResource_init);
			(*env)->SetLongField(env, values[n].l, WLResource_native_ptr, (jlong)(intptr_t)args[n-1].o);
			n++;
		}
		else if(c == 'f') {
			values[n].l = (*env)->NewObject(env, WLFixed_class, WLFixed_init);
			(*env)->SetIntField(env, values[n].l, WLFixed_data, args[n-1].i);
			n++;
		}
	}
	*r_values = values;
	*r_sig = sig;
}

static inline char *get_camel_name(char *name) {
	int i, j, len, first_underscore;
	char *out;

	len = 0;
	for(i = 0; name[i] != '\0'; i++) {
		len += name[i] != '_';
	}

	out = malloc(len + 1);
	first_underscore = 0;
	j = 0;
	for(i = 0; name[i] != '\0'; i++) {
		if(name[i] != '_') {
			if(i == 0) {
				out[j++] = toupper(name[i]);
			}
			else if(name[i - 1] == '_') {
				first_underscore = 1;
				if(i == 1) out[j++] = name[i];
				else out[j++] = toupper(name[i]);
			}
			else if(!first_underscore) {
				out[j++] = toupper(name[i]);
			}
			else {
				out[j++] = name[i];
			}
		}
	}
	out[j++] = '\0';
	return out;
}
