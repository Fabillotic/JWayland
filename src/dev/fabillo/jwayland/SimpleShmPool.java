package dev.fabillo.jwayland;

import java.nio.ByteBuffer;

public final class SimpleShmPool {

    private int fd = -1;
    private ByteBuffer data = null;

    private SimpleShmPool(int fd, ByteBuffer data) {
        this.fd = fd;
        this.data = data;
    }

    public static SimpleShmPool create(int size) {
        int fd = allocate_shm_file(size);
        ByteBuffer data = map_shm(fd, size);
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

    private static native int allocate_shm_file(int size);
    private static native ByteBuffer map_shm(int fd, int size);
    private static native void unmap_shm(ByteBuffer buffer);
    private static native void close_shm_fd(int fd);

    static {
	System.loadLibrary("jwayland");
    }
}

