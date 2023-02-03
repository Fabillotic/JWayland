package dev.fabillo.jwayland;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class JWayland {
	
	private static boolean libraryLoaded = false;
	
	public static void loadLibrary() {
		if(!libraryLoaded) {
			InputStream in = JWayland.class.getResourceAsStream("/libjwayland.so");
			if(in == null) {
				throw new RuntimeException("libjwayland.so not found in classpath!");
			}
			
			File f = new File(System.getProperty("java.io.tmpdir"), "libjwayland.so");
			FileOutputStream out = null;
			
			try {
				out = new FileOutputStream(f);
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
			
			if(out == null) {
				return;
			}
			
			try {
				byte[] b = in.readAllBytes();
				out.write(b);
				out.close();
				in.close();
			} catch(IOException e) {
				e.printStackTrace();
				return;
			}
			
			System.load(f.getAbsolutePath());
			
			libraryLoaded = true;
		}
	}
	
}
