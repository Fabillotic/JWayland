package dev.fabillo.jwayland;

import dev.fabillo.jwayland.protocol.WLCallback;
import dev.fabillo.jwayland.protocol.WLCallback.WLCallbackListener;
import dev.fabillo.jwayland.protocol.WLDisplay;
import dev.fabillo.jwayland.protocol.WLRegistry;
import dev.fabillo.jwayland.protocol.WLRegistry.WLRegistryListener;

public class JWayland {

	public static void main(String[] args) {
		ClientDisplay connection = ClientDisplay.connect("wayland-0");
		
		WLDisplay display = connection.getProxy();
		System.out.println("display: " + display);
		WLProxy p = display.sync();
		System.out.println(p);
		WLCallback c = WLCallback.fromProxy(p);
		c.addListener(new WLCallbackListener() {
			
			@Override
			public void done(int callback_data) {
				System.out.println("Sync done!!!!");
			}
		});
		System.out.println("Sync called!");
		
		WLRegistry registry = WLRegistry.fromProxy(display.get_registry());
		System.out.println("registry: " + registry);
		registry.addListener(new WLRegistryListener() {
			
			@Override
			public void global_remove(int name) {
				
			}
			
			@Override
			public void global(int name, String iface, int version) {
				System.out.println("Global! name: " + name + ", interface: " + iface + ", version: " + version);
			}
		});
		connection.roundtrip();
		
		while(true) {
			connection.dispatch();
		}
	}

}
