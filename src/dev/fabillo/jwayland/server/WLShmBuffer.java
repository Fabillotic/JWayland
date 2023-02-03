package dev.fabillo.jwayland.server;

import java.nio.ByteBuffer;

import dev.fabillo.jwayland.JWayland;
import dev.fabillo.jwayland.WLObject;
import dev.fabillo.jwayland.protocol.server.WLBufferResource;

public class WLShmBuffer extends WLObject {
	
	public WLShmBuffer() {
	}
	
	public WLShmBuffer(long native_ptr) {
		this.native_ptr = native_ptr;
	}
	
	public static native WLShmBuffer get(WLBufferResource resource);
	
	public native int get_stride();
	public native ByteBuffer get_data();
	public native int get_format();
	public native int get_width();
	public native int get_height();
	
	@Override
	public String toString() {
		return "SHM_BUFFER(0x" + Long.toHexString(native_ptr) + ")";
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof WLShmBuffer) {
			if(((WLShmBuffer) obj).native_ptr == native_ptr) return true;
		}
		return false;
	}
	
	static {
		JWayland.loadLibrary();
	}

}
