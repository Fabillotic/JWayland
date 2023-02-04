package dev.fabillo.jwayland.examples;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import java.util.ArrayList;
import java.util.HashMap;

import javax.swing.JFrame;
import javax.swing.JPanel;

import dev.fabillo.jwayland.protocol.server.WLBufferResource;
import dev.fabillo.jwayland.protocol.server.WLCallbackResource;
import dev.fabillo.jwayland.protocol.server.WLCompositorResource;
import dev.fabillo.jwayland.protocol.server.WLCompositorResource.WLCompositorResourceListener;
import dev.fabillo.jwayland.protocol.server.WLSurfaceResource;
import dev.fabillo.jwayland.protocol.server.WLSurfaceResource.WLSurfaceResourceListener;
import dev.fabillo.jwayland.server.ServerDisplay;
import dev.fabillo.jwayland.server.WLClient;
import dev.fabillo.jwayland.server.WLClient.WLClientCreatedListener;
import dev.fabillo.jwayland.server.WLEventLoop;
import dev.fabillo.jwayland.server.WLGlobal;
import dev.fabillo.jwayland.server.WLGlobal.WLGlobalBindListener;
import dev.fabillo.jwayland.server.WLResource;
import dev.fabillo.jwayland.server.WLShmBuffer;

public class JWaylandServerExample extends JPanel {

	private static final long serialVersionUID = 1L;
	
	private JFrame frame;
	private HashMap<WLClient, BufferedImage> imageMap = new HashMap<>();

	public static void main(String[] args) {
		JWaylandServerExample instance = new JWaylandServerExample();
		instance.run();
	}
	
	public void run() {
		frame = new JFrame("JWayland Example Compositor");
		frame.setSize(1000, 750);
		frame.add(this);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
		
		ServerDisplay display = ServerDisplay.create();
		System.out.println("Listening on '" + display.add_socket_auto() + "'...");
		
		ArrayList<WLCallbackResource> callbacks = new ArrayList<WLCallbackResource>();
		
		WLGlobal wl_compositor_global = display.create_global("wl_compositor", 5, new WLGlobalBindListener() {
			
			@Override
			public void bind(WLClient client, int version, int id) {
				System.out.println("Client attempted to bind wl_compositor!");
				WLResource compositor_resource = display.create_resource(client, "wl_compositor", version, id);
				WLCompositorResource compositor = WLCompositorResource.fromResource(compositor_resource);
				compositor.addListener(new WLCompositorResourceListener() {
					
					@Override
					public void create_surface(int id) {
						System.out.println("CREATE SURFACE!");
						WLResource surface_resource = display.create_resource(client, "wl_surface", 5, id);
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
								callbacks.add(callback);
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
							public void attach(WLResource buffer_resource, int x, int y) {
								WLBufferResource buffer = WLBufferResource.fromResource(buffer_resource);
								System.out.println("Attach: " + buffer);
								WLShmBuffer shm_buffer = WLShmBuffer.get(buffer);
								int w = shm_buffer.get_width();
								int h = shm_buffer.get_height();
								int s = shm_buffer.get_stride();
								System.out.println(shm_buffer + ", " + w + ", " + h);
								byte data[] = new byte[s * h];
								shm_buffer.get_data().get(data);
								
								BufferedImage image = new BufferedImage(w, h, BufferedImage.TYPE_4BYTE_ABGR);
								byte[] imgdata = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
								for(int i = 0; i < w * h; i++) {
									imgdata[i * 4 + 1] = data[i * 4 + 0];
									imgdata[i * 4 + 2] = data[i * 4 + 1];
									imgdata[i * 4 + 3] = data[i * 4 + 2];
									imgdata[i * 4 + 0] = data[i * 4 + 3];
								}
								imageMap.put(client, image);
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
		
		display.init_shm();
		
		display.add_client_created_listener(new WLClientCreatedListener() {
			
			@Override
			public void client_created(WLClient client) {
				System.out.println("New client: " + client);
			}
		});
		
		WLEventLoop loop = display.get_event_loop();
		System.out.println(loop);
		
		boolean running = true;
		long last = System.currentTimeMillis();
		while(running) {
			display.flush_clients();
			loop.dispatch(0);
			if(System.currentTimeMillis() - last >= 20) {
				for(WLCallbackResource c : callbacks) {
					c.done(System.currentTimeMillis());
				}
				callbacks.clear();
				this.repaint();
				last = System.currentTimeMillis();
			}
		}
		display.destroy();
	}
	
	@Override
	public void paint(Graphics g) {
		super.paint(g);
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, 1000, 750);
		for(BufferedImage image : imageMap.values()) {
			g.drawImage(image, 0, 0, null);
		}
	}

}
