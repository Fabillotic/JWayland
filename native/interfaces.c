#include <stdio.h>
#include <string.h>
#include <wayland-client-core.h>
#include "interfaces.h"

struct wl_interface wl_display_interface;
struct wl_interface wl_callback_interface;
struct wl_interface wl_registry_interface;
struct wl_interface wp_single_pixel_buffer_manager_v1_interface;
struct wl_interface wl_buffer_interface;

struct wl_interface *interfaces[] = {
	&wl_display_interface,
	&wl_callback_interface,
	&wl_registry_interface,
	&wp_single_pixel_buffer_manager_v1_interface,
	&wl_buffer_interface
};

struct wl_interface *get_interface_by_name(char *name) {
	int i;

	for(i = 0; i < sizeof(interfaces) / sizeof(intptr_t); i++) {
		printf("i: %d, n: %d, s: '%s'\n", i, (sizeof(interfaces) / sizeof(intptr_t)), interfaces[i]->name);
		fflush(stdout);
		if(!strcmp(interfaces[i]->name, name)) {
			return interfaces[i];
		}
	}
	return NULL;
}

/* wl_display */
struct wl_message wl_display_requests[] = {
	{"sync", "n", (struct wl_interface*[]) {&wl_callback_interface}},
	{"get_registry", "n", (struct wl_interface*[]) {&wl_registry_interface}}
};

struct wl_message wl_display_events[] = {
	{"error", "ous", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"delete_id", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_display_interface = {
	"wl_display", 1,
	2, wl_display_requests,
	2, wl_display_events
};

/* wl_callback */
struct wl_message wl_callback_requests[] = {
};

struct wl_message wl_callback_events[] = {
	{"done", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_callback_interface = {
	"wl_callback", 1,
	0, wl_callback_requests,
	1, wl_callback_events
};

/* wl_registry */
struct wl_message wl_registry_requests[] = {
	{"bind", "usun", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}}
};

struct wl_message wl_registry_events[] = {
	{"global", "usu", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"global_remove", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_registry_interface = {
	"wl_registry", 1,
	1, wl_registry_requests,
	2, wl_registry_events
};

/* wp_single_pixel_buffer_manager_v1 */
struct wl_message wp_single_pixel_buffer_manager_v1_requests[] = {
	{"destroy", "", (struct wl_interface*[]) {}},
	{"create_u32_rgba_buffer", "nuuuu", (struct wl_interface*[]) {&wl_buffer_interface, NULL, NULL, NULL, NULL}}
};

struct wl_message wp_single_pixel_buffer_manager_v1_events[] = {
};

struct wl_interface wp_single_pixel_buffer_manager_v1_interface = {
	"wp_single_pixel_buffer_manager_v1", 1,
	2, wp_single_pixel_buffer_manager_v1_requests,
	0, wp_single_pixel_buffer_manager_v1_events
};

/* wl_buffer */
struct wl_message wl_buffer_requests[] = {
	{"destroy", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_buffer_events[] = {
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_interface wl_buffer_interface = {
	"wl_buffer", 1,
	1, wl_buffer_requests,
	1, wl_buffer_events
};
