package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.server.ServerDisplay;
import dev.fabillo.jwayland.server.WLGlobal;
import dev.fabillo.jwayland.server.WLGlobal.WLGlobalBindListener;
import dev.fabillo.jwayland.server.WLResource;

public class JWaylandServerExample {

	public static void main(String[] args) {
		ServerDisplay display = ServerDisplay.create();
		System.out.println("Listening on '" + display.add_socket_auto() + "'...");
		
		WLGlobal wl_compositor_global = display.create_global("wl_compositor", 5, new WLGlobalBindListener() {
			
			@Override
			public void bind(long client, int version, int id) {
				System.out.println("Client attempted to bind wl_compositor!");
				WLResource compositor = display.create_resource(client, "wl_compositor", version, id);
				System.out.println(compositor);
			}
		});
		
		System.out.println(wl_compositor_global);
		
		display.run();
		display.destroy();
	}

}
