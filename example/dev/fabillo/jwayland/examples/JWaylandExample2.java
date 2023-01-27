package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.ClientDisplay;
import dev.fabillo.jwayland.SimpleShmPool;
import dev.fabillo.jwayland.protocol.WLBuffer;
import dev.fabillo.jwayland.protocol.WLCompositor;
import dev.fabillo.jwayland.protocol.WLDisplay;
import dev.fabillo.jwayland.protocol.WLRegistry;
import dev.fabillo.jwayland.protocol.WLRegistry.WLRegistryListener;
import dev.fabillo.jwayland.protocol.WLShm;
import dev.fabillo.jwayland.protocol.WLShmPool;
import dev.fabillo.jwayland.protocol.WLSurface;
import dev.fabillo.jwayland.protocol.WPSinglePixelBufferManagerV1;
import dev.fabillo.jwayland.protocol.WPViewport;
import dev.fabillo.jwayland.protocol.WPViewporter;
import dev.fabillo.jwayland.protocol.XDGSurface;
import dev.fabillo.jwayland.protocol.XDGSurface.XDGSurfaceListener;
import dev.fabillo.jwayland.protocol.XDGToplevel;
import dev.fabillo.jwayland.protocol.XDGToplevel.XDGToplevelListener;
import dev.fabillo.jwayland.protocol.XDGWmBase;
import dev.fabillo.jwayland.protocol.XDGWmBase.XDGWmBaseListener;

public class JWaylandExample2 {
	
	private static final boolean use_spb = false;
	private static WLCompositor compositor;
	private static XDGWmBase wm_base;
	private static WPSinglePixelBufferManagerV1 spbm;
	private static WPViewporter viewporter;
	private static WLShm shm;
	
	public static void main(String[] args) {
		ClientDisplay client_display = ClientDisplay.connect(null);
		WLDisplay display = client_display.getProxy();
		
		WLRegistry registry = WLRegistry.fromProxy(display.get_registry());
		registry.addListener(new WLRegistryListener() {
			
			@Override
			public void global_remove(int arg0) {
				
			}
			
			@Override
			public void global(int arg0, String arg1, int arg2) {
				if(arg1.equals("wl_compositor")) compositor = WLCompositor.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("xdg_wm_base")) wm_base = XDGWmBase.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("wp_single_pixel_buffer_manager_v1")) spbm = WPSinglePixelBufferManagerV1.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("wp_viewporter")) viewporter = WPViewporter.fromProxy(registry.bind(arg0, arg1, arg2));
				else if(arg1.equals("wl_shm")) shm = WLShm.fromProxy(registry.bind(arg0, arg1, arg2));
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
		
		wm_base.addListener(new XDGWmBaseListener() {
			
			@Override
			public void ping(int arg0) {
				System.out.println("PING");
				wm_base.pong(arg0);
			}
		});
		
		WLSurface surface = WLSurface.fromProxy(compositor.create_surface());
		System.out.println("surface: " + surface);
		XDGSurface window = XDGSurface.fromProxy(wm_base.get_xdg_surface(surface));
		System.out.println("window: " + window);
		XDGToplevel toplevel = XDGToplevel.fromProxy(window.get_toplevel());
		
		window.addListener(new XDGSurfaceListener() {
			
			@Override
			public void configure(int arg0) {
				System.out.println("XDG CONFIGURE!");
				window.ack_configure(arg0);
			}
		});
		
		toplevel.set_title("TRANS RIGHTS");
		toplevel.addListener(new XDGToplevelListener() {
			
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
				WLBuffer buf;
				if(use_spb) {
					long b32max = ((long) 1 << 32) - 1;
					double r = 1.0f;
					double g = 0.0f;
					double b = 0.5f;
					double a = 1.0f;
					buf = WLBuffer.fromProxy(spbm.create_u32_rgba_buffer((long) (b32max * r), (long) (b32max * g), (long) (b32max * b), (long) (b32max * a)));
					WPViewport view = WPViewport.fromProxy(viewporter.get_viewport(surface));
					view.set_source(0, 0, 1 << 8, 1 << 8);
					view.set_destination(500, 500);
				}
				else {
					SimpleShmPool spool = SimpleShmPool.create(500 * 500 * 4);
					WLShmPool pool = WLShmPool.fromProxy(shm.create_pool(spool.getFileDescriptor(), 500 * 500 * 4));
					buf = WLBuffer.fromProxy(pool.create_buffer(0, 500, 500, 500 * 4, 1));
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
