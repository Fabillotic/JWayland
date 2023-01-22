package dev.fabillo.jwayland;

import dev.fabillo.jwayland.protocol.WLBuffer;
import dev.fabillo.jwayland.protocol.WLCallback;
import dev.fabillo.jwayland.protocol.WLCallback.WLCallbackListener;
import dev.fabillo.jwayland.protocol.WLDisplay;
import dev.fabillo.jwayland.protocol.WLRegistry;
import dev.fabillo.jwayland.protocol.WLRegistry.WLRegistryListener;
import dev.fabillo.jwayland.protocol.WPSinglePixelBufferManagerV1;

public class JWayland {
	
	private static WPSinglePixelBufferManagerV1 pix;

	public static void main(String[] args) {
		ClientDisplay connection = ClientDisplay.connect(null);
		
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
				if(iface.equals("wp_single_pixel_buffer_manager_v1")) {
					WLProxy proxy = registry.bind(name, iface, version);
					System.out.println("Global proxy: " + proxy);
					if(proxy != null) {
						pix = WPSinglePixelBufferManagerV1.fromProxy(proxy);
					}
				}
			}
		});
		connection.roundtrip();
		
		WLProxy bprox = pix.create_u32_rgba_buffer(127, 127, 127, 127);
		System.out.println("BUFFER CREATED: " + bprox);
		WLBuffer buf = WLBuffer.fromProxy(bprox);
		System.out.println("CALLING DESTROY: " + buf);
		buf.destroy();
		System.out.println("Buffer created and destroyed again!");
		
		while(true) {
			connection.dispatch();
		}
	}

}
