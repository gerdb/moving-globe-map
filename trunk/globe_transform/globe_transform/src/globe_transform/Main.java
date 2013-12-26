/*
 *  Project:      moving globe map
 *  File:         Main.java
 *  Author:       gerd bartelt - www.sebulli.com
 *
 *  Description:  Transform a 2D into a spherical surface
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

package globe_transform;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import javax.imageio.ImageIO;

public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		// Input file name. Size should be 1000x1000, 2000x2000, 4000x4000 ...
		File img = new File("map.png");
		BufferedImage in = null;
		double ZweiPI = 2*Math.PI;
		double segrel ;
		double w2;
		double segw;
		
		// Number of segments
		double segments = 12;
		double width;
		int pc,pcold=0;
		
		// Size of the input file
		int mapsize = 1000;
		
		int halfMapsize = mapsize /2 ;
		
		
		// Read the input file
		try {
			in = ImageIO.read(img);
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		
		// Create an empty output image
		BufferedImage bufferedImage = new BufferedImage(mapsize,mapsize,BufferedImage.TYPE_INT_RGB);
		Graphics g = bufferedImage.getGraphics();
		g.setColor(Color.WHITE);
		g.fillRect(0, 0, mapsize, mapsize);
		
		// The transformation
		segw = ZweiPI / segments;
		for (double w=0;w<ZweiPI;w+=0.0005) {
			int seg = (int)(segments* w/ZweiPI+0.5);
			pc = (int)(100*w/ZweiPI);
			if (pc!= pcold) {
				System.out.println(pc + "%");
			}
			pcold = pc;
			double segoffs = seg * segw;
			double rotate = ZweiPI/segments/2;
			for (double r=1 ; r<halfMapsize ; r+=0.5) {
				segrel = w-segoffs;
				width= mapsize / segments * Math.sin(r*ZweiPI/mapsize) * segrel/segw;

				w2 = Math.atan(width / r);
				w2 += segoffs ;
				int farbe = in.getRGB((int)(halfMapsize+r*Math.sin(w+rotate)), (int)(halfMapsize+r*Math.cos(w+rotate)));
				bufferedImage.setRGB((int)(halfMapsize+r*Math.sin(w2+rotate)), (int)(halfMapsize+r*Math.cos(w2+rotate)), farbe);
			}
		}	

		
		// Save the output picture
		try {
		    // retrieve image
		    File outputfile = new File("globe.png");
		    ImageIO.write(bufferedImage, "png", outputfile);
		} catch (IOException e) {
		
		}
		
		System.out.println("done!");
		

	}

}
