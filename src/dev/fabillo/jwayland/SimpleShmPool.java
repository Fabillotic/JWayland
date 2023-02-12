package dev.fabillo.jwayland;

import java.nio.ByteBuffer;

public final class SimpleShmPool {
	
	private int fd = -1;
	private ByteBuffer data = null;

	private SimpleShmPool(int fd, ByteBuffer data) {
		this.fd = fd;
		this.data = data;
	}

	public static SimpleShmPool create(int size, MappedFlags flags) {
		int fd = allocate_shm_file(size);
		ByteBuffer data = map_shm(fd, size, flags);
		SimpleShmPool pool = new SimpleShmPool(fd, data);
		return pool;
	}

	public void close_fd() {
		if(fd != -1) {
			close_shm_fd(fd);
		}
	}

	public void destroy() {
		close_fd();
		if(data != null) {
			unmap_shm(data);
			data = null;
		}
	}

	public ByteBuffer asByteBuffer() {
		return data;
	}

	public int getFileDescriptor() {
		return fd;
	}

	public static native int allocate_shm_file(int size);
	public static native ByteBuffer map_shm(int fd, int size, MappedFlags flags);
	public static native void unmap_shm(ByteBuffer buffer);
	public static native void close_shm_fd(int fd);
	
	public static enum MappedFlags {
		
		MAP_SHARED, MAP_PRIVATE;
		
	}
	
	static {
		JWayland.loadLibrary();
	}
}
