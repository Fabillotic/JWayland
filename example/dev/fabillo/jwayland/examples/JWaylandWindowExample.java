package dev.fabillo.jwayland.examples;

import dev.fabillo.jwayland.WLFixed;
import dev.fabillo.jwayland.client.ClientDisplay;
import dev.fabillo.jwayland.client.SimpleShmPool;
import dev.fabillo.jwayland.protocol.client.WLBufferProxy;
import dev.fabillo.jwayland.protocol.client.WLCompositorProxy;
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

public class JWaylandWindowExample {
	
	private static final boolean use_spb = true;
	private static WLCompositorProxy compositor;
	private static XDGWmBaseProxy wm_base;
	private static WPSinglePixelBufferManagerV1Proxy spbm;
	private static WPViewporterProxy viewporter;
	private static WLShmProxy shm;
	
	public static void main(String[] args) {
		ClientDisplay display = ClientDisplay.connect(null);
		WLRegistryProxy registry = display.get_registry();
		registry.setListener(new WLRegistryProxyListener() {

			@Override
			public void global(WLRegistryProxy proxy, int name, String iface, int version) {
				if(iface.equals("wl_compositor")) compositor = (WLCompositorProxy) registry.bind(name, iface, version);
				else if(iface.equals("xdg_wm_base")) wm_base = (XDGWmBaseProxy) registry.bind(name, iface, version);
				else if(iface.equals("wp_single_pixel_buffer_manager_v1")) spbm = (WPSinglePixelBufferManagerV1Proxy) registry.bind(name, iface, version);
				else if(iface.equals("wp_viewporter")) viewporter = (WPViewporterProxy) registry.bind(name, iface, version);
				else if(iface.equals("wl_shm")) shm = (WLShmProxy) registry.bind(name, iface, version);
			}

			@Override
			public void global_remove(WLRegistryProxy proxy, int name) {
			}
		});
		
		display.roundtrip();
		
		if(compositor == null) {
			System.out.println("Didn't receive compositor!");
			display.disconnect();
			return;
		}

		if(wm_base == null) {
			System.out.println("Didn't receive wm_base!");
			display.disconnect();
			return;
		}
		
		if(use_spb) {
			if(spbm == null) {
				System.out.println("Didn't receive spbm!");
				display.disconnect();
				return;
			}
			if(viewporter == null) {
				System.out.println("Didn't receive viewporter!");
				display.disconnect();
				return;
			}
		}
		
		wm_base.setListener(new XDGWmBaseProxyListener() {

			@Override
			public void ping(XDGWmBaseProxy proxy, int serial) {
				System.out.println("PING");
				wm_base.pong(serial);
			}
		});
		
		WLSurfaceProxy surface = compositor.create_surface();
		System.out.println("surface: " + surface);
		XDGSurfaceProxy window = wm_base.get_xdg_surface(surface);
		System.out.println("window: " + window);
		XDGToplevelProxy toplevel = window.get_toplevel();
		
		window.setListener(new XDGSurfaceProxyListener() {

			@Override
			public void configure(XDGSurfaceProxy proxy, int serial) {
				System.out.println("XDG CONFIGURE!");
				window.ack_configure(serial);
			}
		});
		
		toplevel.set_title("TRANS RIGHTS");
		toplevel.setListener(new XDGToplevelProxyListener() {

			@Override
			public void configure(XDGToplevelProxy proxy, int width, int height, long states) {
				System.out.println("TOPLEVEL CONFIGURE!");
				if(width > 0 && height > 0) {
					window.ack_configure(0);
				}
			}

			@Override
			public void close(XDGToplevelProxy proxy) {
				System.exit(0);
			}

			@Override
			public void configure_bounds(XDGToplevelProxy proxy, int width, int height) {
			}

			@Override
			public void wm_capabilities(XDGToplevelProxy proxy, long capabilities) {
			}
		});
		
		surface.commit();
		
		boolean first_dispatch = false;
		
		while(true) {
			System.out.println("DISPATCH!");
			display.dispatch();
			if(!first_dispatch) {
				first_dispatch = true;
				WLBufferProxy buf;
				if(use_spb) {
					long b32max = ((long) 1 << 32) - 1;
					double r = 1.0f;
					double g = 0.0f;
					double b = 0.5f;
					double a = 1.0f;
					buf = spbm.create_u32_rgba_buffer((long) (b32max * r), (long) (b32max * g), (long) (b32max * b), (long) (b32max * a));
					WPViewportProxy view = viewporter.get_viewport(surface);
					view.set_source(new WLFixed(0, 0), new WLFixed(0, 0), new WLFixed(1, 0), new WLFixed(1, 0));
					view.set_destination(500, 500);
				}
				else {
					SimpleShmPool spool = SimpleShmPool.create(500 * 500 * 4);
					WLShmPoolProxy pool = shm.create_pool(spool.getFileDescriptor(), 500 * 500 * 4);
					buf = pool.create_buffer(0, 500, 500, 500 * 4, 1);
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
