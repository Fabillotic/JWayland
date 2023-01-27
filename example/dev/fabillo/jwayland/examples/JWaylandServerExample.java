package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.server.ServerDisplay;
import dev.fabillo.jwayland.server.WLGlobal.WLGlobalBindListener;

public class JWaylandServerExample {

	public static void main(String[] args) {
		ServerDisplay display = ServerDisplay.create();
		System.out.println("Listening on '" + display.add_socket_auto() + "'...");
		
		display.create_global("wl_compositor", 5, new WLGlobalBindListener() {
			
			@Override
			public void bind(long client, int version, int id) {
				System.out.println("Client attempted to bind wl_compositor!");
			}
		});
		
		display.run();
		display.destroy();
	}

}
