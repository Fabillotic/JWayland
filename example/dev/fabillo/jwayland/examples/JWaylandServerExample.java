package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.protocol.server.WLCallbackResource;
import dev.fabillo.jwayland.protocol.server.WLCompositorResource;
import dev.fabillo.jwayland.protocol.server.WLCompositorResource.WLCompositorResourceListener;
import dev.fabillo.jwayland.protocol.server.WLSurfaceResource;
import dev.fabillo.jwayland.protocol.server.WLSurfaceResource.WLSurfaceResourceListener;
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
				WLResource compositor_resource = display.create_resource(client, "wl_compositor", version, id);
				WLCompositorResource compositor = WLCompositorResource.fromResource(compositor_resource);
				compositor.addListener(new WLCompositorResourceListener() {
					
					@Override
					public void create_surface(int id) {
						System.out.println("CREATE SURFACE!");
						WLResource surface_resource = display.create_resource(client, "wl_surface", 1, id);
						WLSurfaceResource surface = WLSurfaceResource.fromResource(surface_resource);
						surface.addListener(new WLSurfaceResourceListener() {
							
							@Override
							public void set_opaque_region(WLResource region) {
								
							}
							
							@Override
							public void set_input_region(WLResource region) {
								
							}
							
							@Override
							public void set_buffer_transform(int transform) {
								
							}
							
							@Override
							public void set_buffer_scale(int scale) {
								
							}
							
							@Override
							public void offset(int x, int y) {
								
							}
							
							@Override
							public void frame(int callback_id) {
								System.out.println("Surface frame!");
								WLResource callback_resource = display.create_resource(client, "wl_callback", 1, callback_id);
								WLCallbackResource callback = WLCallbackResource.fromResource(callback_resource);
								System.out.println("Sending done!");
								callback.done(0);
							}
							
							@Override
							public void destroy() {
								
							}
							
							@Override
							public void damage_buffer(int x, int y, int width, int height) {
								
							}
							
							@Override
							public void damage(int x, int y, int width, int height) {
								
							}
							
							@Override
							public void commit() {
								System.out.println("Surface commit!");
							}
							
							@Override
							public void attach(WLResource buffer, int x, int y) {
								
							}
						});
					}
					
					@Override
					public void create_region(int id) {
						
					}
				});
				System.out.println(compositor);
			}
		});
		
		System.out.println(wl_compositor_global);
		
		display.run();
		display.destroy();
	}

}
