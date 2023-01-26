#include <stdio.h>
#include <string.h>
#include <wayland-client-core.h>
#include "interfaces.h"

struct wl_interface wl_display_interface;
struct wl_interface wl_registry_interface;
struct wl_interface wl_callback_interface;
struct wl_interface wl_compositor_interface;
struct wl_interface wl_shm_pool_interface;
struct wl_interface wl_shm_interface;
struct wl_interface wl_buffer_interface;
struct wl_interface wl_data_offer_interface;
struct wl_interface wl_data_source_interface;
struct wl_interface wl_data_device_interface;
struct wl_interface wl_data_device_manager_interface;
struct wl_interface wl_shell_interface;
struct wl_interface wl_shell_surface_interface;
struct wl_interface wl_surface_interface;
struct wl_interface wl_seat_interface;
struct wl_interface wl_pointer_interface;
struct wl_interface wl_keyboard_interface;
struct wl_interface wl_touch_interface;
struct wl_interface wl_output_interface;
struct wl_interface wl_region_interface;
struct wl_interface wl_subcompositor_interface;
struct wl_interface wl_subsurface_interface;
struct wl_interface wp_single_pixel_buffer_manager_v1_interface;

struct wl_interface *interfaces[] = {
	&wl_display_interface,
	&wl_registry_interface,
	&wl_callback_interface,
	&wl_compositor_interface,
	&wl_shm_pool_interface,
	&wl_shm_interface,
	&wl_buffer_interface,
	&wl_data_offer_interface,
	&wl_data_source_interface,
	&wl_data_device_interface,
	&wl_data_device_manager_interface,
	&wl_shell_interface,
	&wl_shell_surface_interface,
	&wl_surface_interface,
	&wl_seat_interface,
	&wl_pointer_interface,
	&wl_keyboard_interface,
	&wl_touch_interface,
	&wl_output_interface,
	&wl_region_interface,
	&wl_subcompositor_interface,
	&wl_subsurface_interface,
	&wp_single_pixel_buffer_manager_v1_interface,
};

struct wl_interface *get_interface_by_name(const char *name) {
	int i;

	for(i = 0; i < sizeof(interfaces) / sizeof(intptr_t); i++) {
		if(!strcmp(interfaces[i]->name, name)) {
			return interfaces[i];
		}
	}
	return NULL;
}


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


struct wl_message wl_compositor_requests[] = {
	{"create_surface", "n", (struct wl_interface*[]) {&wl_surface_interface}},
	{"create_region", "n", (struct wl_interface*[]) {&wl_region_interface}}
};

struct wl_message wl_compositor_events[] = {
};

struct wl_interface wl_compositor_interface = {
	"wl_compositor", 5,
	2, wl_compositor_requests,
	0, wl_compositor_events
};


struct wl_message wl_shm_pool_requests[] = {
	{"create_buffer", "niiiiu", (struct wl_interface*[]) {&wl_buffer_interface, NULL, NULL, NULL, NULL, NULL}},
	{"destroy", "", (struct wl_interface*[]) {}},
	{"resize", "i", (struct wl_interface*[]) {NULL}}
};

struct wl_message wl_shm_pool_events[] = {
};

struct wl_interface wl_shm_pool_interface = {
	"wl_shm_pool", 1,
	3, wl_shm_pool_requests,
	0, wl_shm_pool_events
};


struct wl_message wl_shm_requests[] = {
	{"create_pool", "nhi", (struct wl_interface*[]) {&wl_shm_pool_interface, NULL, NULL}}
};

struct wl_message wl_shm_events[] = {
	{"format", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_shm_interface = {
	"wl_shm", 1,
	1, wl_shm_requests,
	1, wl_shm_events
};


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


struct wl_message wl_data_offer_requests[] = {
	{"accept", "us", (struct wl_interface*[]) {NULL, NULL}},
	{"receive", "sh", (struct wl_interface*[]) {NULL, NULL}},
	{"destroy", "", (struct wl_interface*[]) {}},
	{"finish", "", (struct wl_interface*[]) {}},
	{"set_actions", "uu", (struct wl_interface*[]) {NULL, NULL}}
};

struct wl_message wl_data_offer_events[] = {
	{"offer", "s", (struct wl_interface*[]) {NULL}},
	{"source_actions", "u", (struct wl_interface*[]) {NULL}},
	{"action", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_data_offer_interface = {
	"wl_data_offer", 3,
	5, wl_data_offer_requests,
	3, wl_data_offer_events
};


struct wl_message wl_data_source_requests[] = {
	{"offer", "s", (struct wl_interface*[]) {NULL}},
	{"destroy", "", (struct wl_interface*[]) {}},
	{"set_actions", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_message wl_data_source_events[] = {
	{"target", "s", (struct wl_interface*[]) {NULL}},
	{"send", "sh", (struct wl_interface*[]) {NULL, NULL}},
	{"cancelled", "", (struct wl_interface*[]) {}},
	{"dnd_drop_performed", "", (struct wl_interface*[]) {}},
	{"dnd_finished", "", (struct wl_interface*[]) {}},
	{"action", "u", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_data_source_interface = {
	"wl_data_source", 3,
	3, wl_data_source_requests,
	6, wl_data_source_events
};


struct wl_message wl_data_device_requests[] = {
	{"start_drag", "ooou", (struct wl_interface*[]) {&wl_data_source_interface, &wl_surface_interface, &wl_surface_interface, NULL}},
	{"set_selection", "ou", (struct wl_interface*[]) {&wl_data_source_interface, NULL}},
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_data_device_events[] = {
	{"data_offer", "n", (struct wl_interface*[]) {&wl_data_offer_interface}},
	{"enter", "uoffo", (struct wl_interface*[]) {NULL, &wl_surface_interface, NULL, NULL, &wl_data_offer_interface}},
	{"leave", "", (struct wl_interface*[]) {}},
	{"motion", "uff", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"drop", "", (struct wl_interface*[]) {}},
	{"selection", "o", (struct wl_interface*[]) {&wl_data_offer_interface}}
};

struct wl_interface wl_data_device_interface = {
	"wl_data_device", 3,
	3, wl_data_device_requests,
	6, wl_data_device_events
};


struct wl_message wl_data_device_manager_requests[] = {
	{"create_data_source", "n", (struct wl_interface*[]) {&wl_data_source_interface}},
	{"get_data_device", "no", (struct wl_interface*[]) {&wl_data_device_interface, &wl_seat_interface}}
};

struct wl_message wl_data_device_manager_events[] = {
};

struct wl_interface wl_data_device_manager_interface = {
	"wl_data_device_manager", 3,
	2, wl_data_device_manager_requests,
	0, wl_data_device_manager_events
};


struct wl_message wl_shell_requests[] = {
	{"get_shell_surface", "no", (struct wl_interface*[]) {&wl_shell_surface_interface, &wl_surface_interface}}
};

struct wl_message wl_shell_events[] = {
};

struct wl_interface wl_shell_interface = {
	"wl_shell", 1,
	1, wl_shell_requests,
	0, wl_shell_events
};


struct wl_message wl_shell_surface_requests[] = {
	{"pong", "u", (struct wl_interface*[]) {NULL}},
	{"move", "ou", (struct wl_interface*[]) {&wl_seat_interface, NULL}},
	{"resize", "ouu", (struct wl_interface*[]) {&wl_seat_interface, NULL, NULL}},
	{"set_toplevel", "", (struct wl_interface*[]) {}},
	{"set_transient", "oiiu", (struct wl_interface*[]) {&wl_surface_interface, NULL, NULL, NULL}},
	{"set_fullscreen", "uuo", (struct wl_interface*[]) {NULL, NULL, &wl_output_interface}},
	{"set_popup", "ouoiiu", (struct wl_interface*[]) {&wl_seat_interface, NULL, &wl_surface_interface, NULL, NULL, NULL}},
	{"set_maximized", "o", (struct wl_interface*[]) {&wl_output_interface}},
	{"set_title", "s", (struct wl_interface*[]) {NULL}},
	{"set_class", "s", (struct wl_interface*[]) {NULL}}
};

struct wl_message wl_shell_surface_events[] = {
	{"ping", "u", (struct wl_interface*[]) {NULL}},
	{"configure", "uii", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"popup_done", "", (struct wl_interface*[]) {}}
};

struct wl_interface wl_shell_surface_interface = {
	"wl_shell_surface", 1,
	10, wl_shell_surface_requests,
	3, wl_shell_surface_events
};


struct wl_message wl_surface_requests[] = {
	{"destroy", "", (struct wl_interface*[]) {}},
	{"attach", "oii", (struct wl_interface*[]) {&wl_buffer_interface, NULL, NULL}},
	{"damage", "iiii", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"frame", "n", (struct wl_interface*[]) {&wl_callback_interface}},
	{"set_opaque_region", "o", (struct wl_interface*[]) {&wl_region_interface}},
	{"set_input_region", "o", (struct wl_interface*[]) {&wl_region_interface}},
	{"commit", "", (struct wl_interface*[]) {}},
	{"set_buffer_transform", "i", (struct wl_interface*[]) {NULL}},
	{"set_buffer_scale", "i", (struct wl_interface*[]) {NULL}},
	{"damage_buffer", "iiii", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"offset", "ii", (struct wl_interface*[]) {NULL, NULL}}
};

struct wl_message wl_surface_events[] = {
	{"enter", "o", (struct wl_interface*[]) {&wl_output_interface}},
	{"leave", "o", (struct wl_interface*[]) {&wl_output_interface}}
};

struct wl_interface wl_surface_interface = {
	"wl_surface", 5,
	11, wl_surface_requests,
	2, wl_surface_events
};


struct wl_message wl_seat_requests[] = {
	{"get_pointer", "n", (struct wl_interface*[]) {&wl_pointer_interface}},
	{"get_keyboard", "n", (struct wl_interface*[]) {&wl_keyboard_interface}},
	{"get_touch", "n", (struct wl_interface*[]) {&wl_touch_interface}},
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_seat_events[] = {
	{"capabilities", "u", (struct wl_interface*[]) {NULL}},
	{"name", "s", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_seat_interface = {
	"wl_seat", 8,
	4, wl_seat_requests,
	2, wl_seat_events
};


struct wl_message wl_pointer_requests[] = {
	{"set_cursor", "uoii", (struct wl_interface*[]) {NULL, &wl_surface_interface, NULL, NULL}},
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_pointer_events[] = {
	{"enter", "uoff", (struct wl_interface*[]) {NULL, &wl_surface_interface, NULL, NULL}},
	{"leave", "uo", (struct wl_interface*[]) {NULL, &wl_surface_interface}},
	{"motion", "uff", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"button", "uuuu", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"axis", "uuf", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"frame", "", (struct wl_interface*[]) {}},
	{"axis_source", "u", (struct wl_interface*[]) {NULL}},
	{"axis_stop", "uu", (struct wl_interface*[]) {NULL, NULL}},
	{"axis_discrete", "ui", (struct wl_interface*[]) {NULL, NULL}},
	{"axis_value120", "ui", (struct wl_interface*[]) {NULL, NULL}}
};

struct wl_interface wl_pointer_interface = {
	"wl_pointer", 8,
	2, wl_pointer_requests,
	10, wl_pointer_events
};


struct wl_message wl_keyboard_requests[] = {
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_keyboard_events[] = {
	{"keymap", "uhu", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"enter", "uoa", (struct wl_interface*[]) {NULL, &wl_surface_interface, NULL}},
	{"leave", "uo", (struct wl_interface*[]) {NULL, &wl_surface_interface}},
	{"key", "uuuu", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"modifiers", "uuuuu", (struct wl_interface*[]) {NULL, NULL, NULL, NULL, NULL}},
	{"repeat_info", "ii", (struct wl_interface*[]) {NULL, NULL}}
};

struct wl_interface wl_keyboard_interface = {
	"wl_keyboard", 8,
	1, wl_keyboard_requests,
	6, wl_keyboard_events
};


struct wl_message wl_touch_requests[] = {
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_touch_events[] = {
	{"down", "uuoiff", (struct wl_interface*[]) {NULL, NULL, &wl_surface_interface, NULL, NULL, NULL}},
	{"up", "uui", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"motion", "uiff", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"frame", "", (struct wl_interface*[]) {}},
	{"cancel", "", (struct wl_interface*[]) {}},
	{"shape", "iff", (struct wl_interface*[]) {NULL, NULL, NULL}},
	{"orientation", "if", (struct wl_interface*[]) {NULL, NULL}}
};

struct wl_interface wl_touch_interface = {
	"wl_touch", 8,
	1, wl_touch_requests,
	7, wl_touch_events
};


struct wl_message wl_output_requests[] = {
	{"release", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_output_events[] = {
	{"geometry", "iiiiissi", (struct wl_interface*[]) {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL}},
	{"mode", "uiii", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"done", "", (struct wl_interface*[]) {}},
	{"scale", "i", (struct wl_interface*[]) {NULL}},
	{"name", "s", (struct wl_interface*[]) {NULL}},
	{"description", "s", (struct wl_interface*[]) {NULL}}
};

struct wl_interface wl_output_interface = {
	"wl_output", 4,
	1, wl_output_requests,
	6, wl_output_events
};


struct wl_message wl_region_requests[] = {
	{"destroy", "", (struct wl_interface*[]) {}},
	{"add", "iiii", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}},
	{"subtract", "iiii", (struct wl_interface*[]) {NULL, NULL, NULL, NULL}}
};

struct wl_message wl_region_events[] = {
};

struct wl_interface wl_region_interface = {
	"wl_region", 1,
	3, wl_region_requests,
	0, wl_region_events
};


struct wl_message wl_subcompositor_requests[] = {
	{"destroy", "", (struct wl_interface*[]) {}},
	{"get_subsurface", "noo", (struct wl_interface*[]) {&wl_subsurface_interface, &wl_surface_interface, &wl_surface_interface}}
};

struct wl_message wl_subcompositor_events[] = {
};

struct wl_interface wl_subcompositor_interface = {
	"wl_subcompositor", 1,
	2, wl_subcompositor_requests,
	0, wl_subcompositor_events
};


struct wl_message wl_subsurface_requests[] = {
	{"destroy", "", (struct wl_interface*[]) {}},
	{"set_position", "ii", (struct wl_interface*[]) {NULL, NULL}},
	{"place_above", "o", (struct wl_interface*[]) {&wl_surface_interface}},
	{"place_below", "o", (struct wl_interface*[]) {&wl_surface_interface}},
	{"set_sync", "", (struct wl_interface*[]) {}},
	{"set_desync", "", (struct wl_interface*[]) {}}
};

struct wl_message wl_subsurface_events[] = {
};

struct wl_interface wl_subsurface_interface = {
	"wl_subsurface", 1,
	6, wl_subsurface_requests,
	0, wl_subsurface_events
};


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
