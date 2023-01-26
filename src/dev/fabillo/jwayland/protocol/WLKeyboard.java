package dev.fabillo.jwayland.protocol;

import dev.fabillo.jwayland.WLProxy;
import dev.fabillo.jwayland.annotation.ProxyListener;
import dev.fabillo.jwayland.annotation.WLEvent;
import dev.fabillo.jwayland.annotation.WLRequest;

public class WLKeyboard extends WLProxy {
	
	public static WLKeyboard fromProxy(WLProxy proxy) {
		if(proxy == null) return null;
		WLKeyboard type = new WLKeyboard();
		type.native_ptr = proxy.native_ptr;
		return type;
	}
	
	@ProxyListener
	public native void addListener(WLKeyboardListener listener);
	
	@WLRequest
	public native void release();
	
	public static interface WLKeyboardListener {
		
		@WLEvent
		public void keymap(int format, int fd, int size);
		
		@WLEvent
		public void enter(int serial, WLProxy surface, long keys);
		
		@WLEvent
		public void leave(int serial, WLProxy surface);
		
		@WLEvent
		public void key(int serial, int time, int key, int state);
		
		@WLEvent
		public void modifiers(int serial, int mods_depressed, int mods_latched, int mods_locked, int group);
		
		@WLEvent
		public void repeat_info(int rate, int delay);
		
	}
	
	static {
		System.loadLibrary("jwayland");
	}
	
}
