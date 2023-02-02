package dev.fabillo.jwayland.server;

import dev.fabillo.jwayland.WLObject;

public class WLClient extends WLObject {
	
	public WLClient() {
	}
	
	public WLClient(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	@Override
	public String toString() {
		return "CLIENT(0x" + Long.toHexString(native_ptr) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLClient) {
			if(((WLClient) obj).native_ptr == native_ptr) return true;
		}
		return false;
	}
	
	public static interface WLClientCreatedListener {
		
		public void client_created(long client);
		
	}
	
	public static interface WLClientDestroyedListener {
		
		public void client_destroyed(long client);
		
	}

}
