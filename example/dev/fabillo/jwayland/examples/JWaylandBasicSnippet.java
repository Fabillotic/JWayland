package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.client.ClientDisplay;
import dev.fabillo.jwayland.client.WLProxy;
import dev.fabillo.jwayland.protocol.client.WLBufferProxy;
import dev.fabillo.jwayland.protocol.client.WLCallbackProxy;
import dev.fabillo.jwayland.protocol.client.WLCallbackProxy.WLCallbackProxyListener;
import dev.fabillo.jwayland.protocol.client.WLRegistryProxy;
import dev.fabillo.jwayland.protocol.client.WLRegistryProxy.WLRegistryProxyListener;
import dev.fabillo.jwayland.protocol.client.WPSinglePixelBufferManagerV1Proxy;

public class JWaylandBasicSnippet {
	
	private static WPSinglePixelBufferManagerV1Proxy pix;

	public static void main(String[] args) {
		ClientDisplay display = ClientDisplay.connect(null);
		System.out.println("display: " + display);
		WLCallbackProxy c = display.sync();
		System.out.println(c);
		c.setListener(new WLCallbackProxyListener() {
			
			@Override
			public void done(WLCallbackProxy callback, int callback_data) {
				System.out.println("Sync done!!!!");
			}
		});
		System.out.println("Sync called!");
		
		WLRegistryProxy registry = display.get_registry();
		System.out.println("registry: " + registry);
		registry.setListener(new WLRegistryProxyListener() {
			
			@Override
			public void global_remove(WLRegistryProxy proxy, int name) {
				
			}
			
			@Override
			public void global(WLRegistryProxy registry, int name, String iface, int version) {
				System.out.println("Global! name: " + name + ", interface: " + iface + ", version: " + version);
				if(iface.equals("wp_single_pixel_buffer_manager_v1")) {
					WLProxy proxy = registry.bind(name, iface, version);
					System.out.println("Global proxy: " + proxy);
					pix = (WPSinglePixelBufferManagerV1Proxy) proxy;
				}
			}
		});
		display.roundtrip();
		
		WLBufferProxy buf = pix.create_u32_rgba_buffer(127, 127, 127, 127);
		System.out.println("BUFFER CREATED: " + buf);
		System.out.println("CALLING DESTROY: " + buf);
		buf.destroy();
		System.out.println("Buffer created and destroyed again!");
		
		while(true) {
			display.dispatch();
		}
	}

}
