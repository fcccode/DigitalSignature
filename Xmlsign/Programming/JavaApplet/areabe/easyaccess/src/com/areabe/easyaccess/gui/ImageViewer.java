package com.areabe.easyaccess.gui;

import java.awt.*;
public class ImageViewer extends Panel {
Toolkit tk = Toolkit.getDefaultToolkit();
    // reference handle for the image
    private Image img = null;

    /**
     * Custom constructor
     */
    public ImageViewer(Image i) {
        super();
        img = i;
    }

    /**
     * We need to override the paintComponent method
     * in order to display the image.
     */
    public void paint(Graphics g) {
        g.drawImage(img, 0, 0, this);
    }

    public void setImage(Image i){
      img = i;
      this.repaint();
    }
/*
    public void addNotify()
    {
            super.addNotify();
            Insets insets = getInsets();
            Dimension scr = tk.getScreenSize();
            Dimension imgSize = new Dimension(img.getWidth(this),img.getHeight(this));
            setBounds((scr.width/2) - (imgSize.width/2),
                    (scr.height/2) - (imgSize.height/2),
                    imgSize.width +insets.left+insets.right,
                    imgSize.height +insets.top+insets.bottom);
    }
    public void paint(Graphics g)
    {
            Insets insets = getInsets();
            g.drawImage(img, insets.left, insets.top,this);
    }
*/
    public void update(Graphics g)
    {
            paint(g);
    }

}
