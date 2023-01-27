package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.client.ClientDisplay;
import dev.fabillo.jwayland.client.SimpleShmPool;
import dev.fabillo.jwayland.protocol.client.WLBufferProxy;
import dev.fabillo.jwayland.protocol.client.WLCompositorProxy;
import dev.fabillo.jwayland.protocol.client.WLDisplayProxy;
import dev.fabillo.jwayland.protocol.client.WLRegistryProxy;
import dev.fabillo.jwayland.protocol.client.WLRegistryProxy.WLRegistryProxyListener;
import dev.fabillo.jwayland.protocol.client.WLShmPoolProxy;
import dev.fabillo.jwayland.protocol.client.WLShmProxy;
import dev.fabillo.jwayland.protocol.client.WLSurfaceProxy;
import dev.fabillo.jwayland.protocol.client.WPSinglePixelBufferManagerV1Proxy;
import dev.fabillo.jwayland.protocol.client.WPViewportProxy;
import dev.fabillo.jwayland.protocol.client.WPViewporterProxy;
import dev.fabillo.jwayland.protocol.client.XDGSurfaceProxy;
import dev.fabillo.jwayland.protocol.client.XDGSurfaceProxy.XDGSurfaceProxyListener;
import dev.fabillo.jwayland.protocol.client.XDGToplevelProxy;
import dev.fabillo.jwayland.protocol.client.XDGToplevelProxy.XDGToplevelProxyListener;
import dev.fabillo.jwayland.protocol.client.XDGWmBaseProxy;
import dev.fabillo.jwayland.protocol.client.XDGWmBaseProxy.XDGWmBaseProxyListener;

public class JWaylandExample2 {
	
	private static final boolean use_spb = false;
	private static WLCompositorProxy compositor;
	private static XDGWmBaseProxy wm_base;
	private static WPSinglePixelBufferManagerV1Proxy spbm;
	private static WPViewporterProxy viewporter;
	private static WLShmProxy shm;
	
	public static void main(String[] args) {
		ClientDisplay client_display = ClientDisplay.connect(null);
		WLDisplayProxy display = client_display.getProxy();
		
		WLRegistryProxy registry = WLRegistryProxy.fromProxy(display.get_registry());
		registry.addListener(new WLRegistryProxyListener() {
			
			@Override
			public void global_remove(int arg0) {
				
			}
			
			@Override
			public void global(int arg0, String arg1, int arg2) {
				if(arg1.equals("wl_compositor")) compositor = WLCompositorProxy.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("xdg_wm_base")) wm_base = XDGWmBaseProxy.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("wp_single_pixel_buffer_manager_v1")) spbm = WPSinglePixelBufferManagerV1Proxy.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("wp_viewporter")) viewporter = WPViewporterProxy.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("wl_shm")) shm = WLShmProxy.fromProxy(registry.bind(arg0, arg1, arg2));
			}
		});
		
		client_display.roundtrip();
		
		if(compositor == null) {
			System.out.println("Didn't receive compositor!");
			client_display.disconnect();
			return;
		}

		if(wm_base == null) {
			System.out.println("Didn't receive wm_base!");
			client_display.disconnect();
			return;
		}
		
		if(spbm == null && use_spb) {
			System.out.println("Didn't receive spbm!");
			client_display.disconnect();
			return;
		}

		if(viewporter == null && use_spb) {
			System.out.println("Didn't receive viewporter!");
			client_display.disconnect();
			return;
		}
		
		wm_base.addListener(new XDGWmBaseProxyListener() {
			
			@Override
			public void ping(int arg0) {
				System.out.println("PING");
				wm_base.pong(arg0);
			}
		});
		
		WLSurfaceProxy surface = WLSurfaceProxy.fromProxy(compositor.create_surface());
		System.out.println("surface: " + surface);
		XDGSurfaceProxy window = XDGSurfaceProxy.fromProxy(wm_base.get_xdg_surface(surface));
		System.out.println("window: " + window);
		XDGToplevelProxy toplevel = XDGToplevelProxy.fromProxy(window.get_toplevel());
		
		window.addListener(new XDGSurfaceProxyListener() {
			
			@Override
			public void configure(int arg0) {
				System.out.println("XDG CONFIGURE!");
				window.ack_configure(arg0);
			}
		});
		
		toplevel.set_title("TRANS RIGHTS");
		toplevel.addListener(new XDGToplevelProxyListener() {
			
			@Override
			public void wm_capabilities(long arg0) {
				
			}
			
			@Override
			public void configure_bounds(int arg0, int arg1) {
				
			}
			
			@Override
			public void configure(int arg0, int arg1, long arg2) {
				System.out.println("TOPLEVEL CONFIGURE!");
				if(arg0 > 0 && arg1 > 0) {
					window.ack_configure(0);
				}
			}
			
			@Override
			public void close() {
				System.exit(0);
			}
		});
		
		surface.commit();
		
		boolean first_dispatch = false;
		
		while(true) {
			System.out.println("DISPATCH!");
			client_display.dispatch();
			if(!first_dispatch) {
				first_dispatch = true;
				WLBufferProxy buf;
				if(use_spb) {
					long b32max = ((long) 1 << 32) - 1;
					double r = 1.0f;
					double g = 0.0f;
					double b = 0.5f;
					double a = 1.0f;
					buf = WLBufferProxy.fromProxy(spbm.create_u32_rgba_buffer((long) (b32max * r), (long) (b32max * g), (long) (b32max * b), (long) (b32max * a)));
					WPViewportProxy view = WPViewportProxy.fromProxy(viewporter.get_viewport(surface));
					view.set_source(0, 0, 1 << 8, 1 << 8);
					view.set_destination(500, 500);
				}
				else {
					SimpleShmPool spool = SimpleShmPool.create(500 * 500 * 4);
					WLShmPoolProxy pool = WLShmPoolProxy.fromProxy(shm.create_pool(spool.getFileDescriptor(), 500 * 500 * 4));
					buf = WLBufferProxy.fromProxy(pool.create_buffer(0, 500, 500, 500 * 4, 1));
					pool.destroy();
					spool.close_fd();
					byte[] src = new byte[500 * 500 * 4];
					for(int i = 0; i < 500 * 500; i++) {
						src[i * 4 + 0] = (byte) 255;
						src[i * 4 + 1] = (byte) 255;
						src[i * 4 + 2] = (byte) 0;
						src[i * 4 + 3] = (byte) 255;
					}
					spool.asByteBuffer().put(src);
					spool.destroy();
				}
				surface.damage(0, 0, 500, 500);
				surface.attach(buf, 0, 0);
				surface.commit();
			}
		}
	}

}
