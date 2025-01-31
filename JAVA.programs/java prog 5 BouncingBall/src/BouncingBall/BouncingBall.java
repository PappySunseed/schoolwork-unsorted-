//program 5 bouncing ball - CMSC 3320/001 - Group 7
//
//Caleb Ruby - rub4133@pennwest.edu
//Adir Turgeman - tur28711@pennwest.edu
//Caleb Rachocki - rac3146@pennwest.edu
//Ryan Miller - mil0780@pennwest.edu

package BouncingBall;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;

public class BouncingBall extends Frame implements WindowListener, ComponentListener, ActionListener, AdjustmentListener, Runnable, MouseListener, MouseMotionListener
{	

	//object class
	class Objc extends Canvas
	{
	//initialization 
		private static final long serialVersionUID = 11L;
		private int ScreenWidth;
		private int ScreenHeight;
		private int SObj;
		
		private int x,y;
		private boolean rect = true;
		private boolean clear = false;
		
		private boolean tail = true;	//tail flag(?)
		
		//movement variables
		int ymin;
		int ymax;
		int xmin;
		int xmax;
		int xold;
		int yold;
		
		boolean right, down;
		
		Image buffer;
		Graphics g;
		
		Vector<Rectangle> walls = new Vector<Rectangle>();
		private final Rectangle ZERO = new Rectangle(0,0,0,0);
		private Rectangle ball = new Rectangle(0,0,0,0);
		
		int rectX, rectY, rectWidth, rectHeight;
		
	//constructor
		public Objc(int SB, int w, int h	)
		{
			down = true;
			right = true;
			
			
			ScreenWidth = w;
			ScreenHeight = h;
			SObj = SB;
			rect = false;
			clear = false;
			
			calcMinMax();
			y = ymin;
			x = xmin;	
			
			ball.setBounds(x, y, SObj, SObj);
			
		}
		
	//mutators
		public void rectangle(boolean r)
		{
			rect = r;	
			
			
			
		}
		public void update(Graphics g)		
		{
			paint(g);
		}
		public void reSize(int w,int h)
		{
			ScreenWidth = w;
			ScreenHeight = h;
			y = ScreenHeight/2;
			x = ScreenWidth/2;
			calcMinMax();
			move();
		}
		public void Clear()
		{
			clear = true;
		}
		public void setX(int newX)
		{
			this.x = newX;
		}
		public void setY(int newY)
		{
			this.y = newY;
		}
		public void setTail(boolean tail)
		{
			this.tail = tail;
		}
		
		public void addOne(Rectangle r)
		{
			walls.addElement(new Rectangle (r));
		}
		public void removeOne(int i)
		{
			walls.removeElementAt(i);
		}
	//paint methods
		
		public void paint(Graphics cg)
		{
			buffer = createImage(getWidth(), getHeight());
			
			if(g != null)
			{
				g.dispose();
			}
			g = buffer.getGraphics();	
			if(clear)
			{
				super.paint(g);
				clear = false;
				g.setColor(Color.red);
				g.drawRect(0,0,ScreenWidth-1,ScreenHeight-1);
			}
			if(rect)
			{
				calcMinMax();
				if(!started)
				{
					x = xmin;
					y = ymin;
				}
				g.setColor(Color.lightGray);
				g.fillRect(x-(SObj-1)/2, y-(SObj-1)/2, SObj, SObj);
				g.setColor(Color.black);
				g.drawRect(x-(SObj-1)/2, y-(SObj-1)/2, SObj-1, SObj-1);
			}
			else
			{
				g.setColor(Color.lightGray);
				g.fillOval(x-(SObj-1)/2, y-(SObj-1)/2, SObj, SObj);
				g.setColor(Color.black);
				g.drawOval(x-(SObj-1)/2, y-(SObj-1)/2, SObj-1, SObj-1);
				ball.setBounds(x-(SObj-1)/2, y-(SObj-1)/2, SObj, SObj);
			}
			
			Rectangle temp = new Rectangle();
			
			if(Obj.rectX != 0)
			{
				g.drawRect(Obj.rectX, Obj.rectY, Obj.rectWidth, Obj.rectHeight);
			}
			
			

			
			for(int i = 0; i < Obj.walls.size(); i++)
			{
			    temp.setBounds(Obj.walls.elementAt(i));
			    //System.out.println("Rectangle " + i + ": " + temp);
			    g.fillRect(temp.x, temp.y, temp.width, temp.height);
			}
		
			
			
			xold = x;
			yold = y;
			
			
			cg.drawImage(buffer, 0, 0, null);
		}
			

	//accessors
		public int getObjectSize()
		{
			return this.SObj;
		}
		public int getObjectX()
		{
			return this.x;
		}
		public int getObjectY()
		{
			return this.y;
		}
		public boolean getTail()
		{
			return this.tail;
		}
		
		public Rectangle getOne(int i)
		{
			return walls.elementAt(i);
		}
		public int getWallSize()
		{
			return walls.size();
		}
	//calculate min and max 
		public void calcMinMax() 
		{
			ymin = 0 + (SObj - 1) / 2;  // Adjusted space needed for half object
		    ymax = this.ScreenHeight - (SObj - 1) / 2;
		    xmin = 0 + (SObj - 1) / 2;
		    xmax = this.ScreenWidth - (SObj - 1) / 2;
		   
		    
		}
		
	//size method
		public void ObjSize(int newSize)
		{
			SObj = newSize;
			ball.setBounds(x, y, SObj, SObj);
		}
		
	//check x and y 
		public boolean checkX(int x)
		{
			if(x < xmin || x > xmax)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		public boolean checkY(int y)
		{
			if(y < ymin || y > ymax)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		
	//move
		public void move()
		{
			if(!checkX(x))
			{
				right = !right;
			}
			if(!checkY(y))
			{
				down = !down;
			}
			
			ball.grow(1, 1);
			Rectangle touchedRect = isTouch(ball);
			if (touchedRect != null) {
			    int xline = touchedRect.x;
			    int yline = touchedRect.y;

			    Rectangle leftBound = new Rectangle(xline, yline + 1, 1, touchedRect.height - 1);
			    Rectangle rightBound = new Rectangle(xline + touchedRect.width - 1, yline + 1, 1, touchedRect.height - 1);

			    Rectangle topBound = new Rectangle(xline + 1, yline, touchedRect.width, 3);
			    Rectangle bottomBound = new Rectangle(xline + 1, yline + touchedRect.height - 1, touchedRect.width, 3);

			    if (ball.intersects(leftBound)) {
			        right = false;
			    }
			    if (ball.intersects(rightBound)) {
			        right = true;
			    }
			    
			    if (ball.intersects(topBound)) {
			        down = !down;
			    }
			    if (ball.intersects(bottomBound)) {
			        down = !down;
			    }
			}

			
			
			if(right)
			{
				x++;
			}
			else
			{
				x--;
			}
			
			if(down)
			{
				y--;
				
			}
			else
			{
				y++;
			}
			
			
		}

	//is ball to the wall 
		public Rectangle isTouch(Rectangle ball)
		{
			Rectangle r = new Rectangle(ZERO);
			Rectangle b = new Rectangle(ball);
			b.grow(1, 1);
			int i =0;
			boolean ok = true;
			
			
			while((i<walls.size())&&ok)
			{
				r=walls.elementAt(i);
				if(r.intersects(b))
				{
					
					return r;
					
				}
				else
				{
					i++;
				}
			}
			return ZERO;
			
		}
		
		


	
		
		
		

		
	}
	
	
	
	//initialization
		// Initial application serial number UID
		private static final long serialVersionUID = 10L;
		
		// Initial constants
		private final int WIDTH = 640;
		private final int HEIGHT = 400;
		private final int BUTTONH = 20;
		private final int BUTTONHS = 5;
		
		// initial varibles
		private int WinWidth = WIDTH;
		private int WinHeight = HEIGHT;
		private int ScreenWidth;
		private int ScreenHeight;
		private int WinTop = 10;
		private int WinLeft = 50;
		private int BUTTONW = 50;
		private int Center = (WIDTH/2);
		private int BUTTONS = BUTTONW/4;
		
		// create inset
		private Insets i;
		
		// create buttons
		Button start, shape, clear, tail, quit;
			
		//scrollbar & circle/rectangle constants
		private final int MAXObj = 100;	//max object size 
		private final int MINObj = 10; 	//min object size 
		private final int SPEED = 50;	//initial speed
		private final int SBvisible = 10;	//visible scroll bar
		private final int SBunit = 1;	//scrollbar unit step size 
		private final int SBblock = 10;	//scroll bar block step size 
		private final int SCROLLBARH = BUTTONH;	//scrollbar height 
		private final int SOBJ = 21;	//initial object width 
	
		//scrollbar & circle/rectangle variables
		private int SObj = SOBJ;	//initial object width
		private int SpeedSBmin = 1; //speed scrollbar minimum value 
		private int SpeedSBmax = 100+SBvisible;	//speed scrollbar maximum value with visible offset 
		private int SpeedSBinit = SPEED;	//initial speed scrollbar value 
		private int ScrollBarW;	//scrollbar width 
	
		
		//objects
		private Objc Obj;	//object to draw 
		private Label SPEEDL = new Label("Speed", Label.CENTER);
		private Label SIZEL = new Label("Size", Label.CENTER);
		Scrollbar SpeedScrollBar, ObjSizeScrollBar;
		
		///rectangles 
		private Rectangle Perimeter = new Rectangle(0, 0, WIDTH, HEIGHT);	//ball perimeter 
		private Rectangle db = new Rectangle(0,0,0,0);		//drag box 
		
		//mouse points 
		Point m1 = new Point(0,0);
		Point m2 = new Point(0,0);
		
		
//thread initializing
	//constants
	private final double DELAY = .9;	//value for min time delay, may need tweaked
	
	//variables
	boolean run;	//program loop
	boolean TimePause;	//identify run/pause
	boolean started;	//identify if animation started
	int speed;	//scrollbar speed
	int delay;	//current time delay
	
	//objects
	private Thread thethread;
		
	//p5 addition
	private Panel sheet = new Panel();	//
	private Panel control = new Panel();
	
	
	// bouce constructor
	public BouncingBall()
	{
		Perimeter.grow(-1, -1);
		
		started = false;	//started flag for thread
		
		setLayout(new BorderLayout());		//p5 apply border layout to frame 
		setVisible(true);
		MakeSheet();
		try
		{
			initComponents();
		}
		catch(Exception e)
		{
			e.printStackTrace();
		}
		SizeScreen();
		
		start();
	}

//null layout methods, window size, button layout 
	private void MakeSheet()
	{
		i = getInsets();
		// create screen size 
		ScreenWidth = WinWidth-i.left-i.right;
		// create screen height
		ScreenHeight = WinHeight-i.top-(BUTTONH+BUTTONHS)- i.bottom;
		setSize(WinWidth, WinHeight);
		Center = (ScreenWidth/2);
		BUTTONW = (ScreenWidth/11);
		BUTTONS = BUTTONW/4;
		setBackground(Color.LIGHT_GRAY);
		
		ScrollBarW = 2*BUTTONW;	//set new width for the scroll bar 
	}	
	public void initComponents() throws Exception, IOException {
	    TimePause = true;
	    run = true;

	    this.resize(641,400);
	    
	    setPreferredSize(new Dimension(WIDTH,HEIGHT));
		setMinimumSize (getPreferredSize());
	    
	    
	    this.setLayout(new BorderLayout()); // Set the layout of the Frame to BorderLayout

	    sheet = new Panel(new BorderLayout(0,0));
	    sheet.setBackground(Color.blue);


	    Obj = new Objc(SObj, sheet.getWidth(), sheet.getHeight()); // Set the size of Obj to match the size of sheet
	    Obj.setBackground(Color.white);
	    Obj.setBounds(Perimeter);
	    Obj.addMouseListener(this);
	    Obj.addMouseMotionListener(this);
	    sheet.add(Obj, BorderLayout.CENTER); // Add Obj to the center of sheet
	    Perimeter.setBounds(sheet.getBounds());

	    control = new Panel(new GridBagLayout());
	    GridBagConstraints gbc = new GridBagConstraints();
	    gbc.gridwidth = 1;
	    gbc.gridheight = 10;
	    gbc.weightx = 0.3;
	    gbc.anchor = GridBagConstraints.WEST;

	    start = new Button("Run");
	    control.add(start, gbc);
	    control.setBackground(Color.lightGray);
	    
	    shape = new Button("Circle");
	    clear = new Button("Clear");
	    tail = new Button("No tail");
	    quit = new Button("Quit");

	   // control.add(shape, gbc);
	    control.add(clear, gbc);
	  //  control.add(tail, gbc);
	    control.add(quit, gbc);

	    start.addActionListener(this);
	    shape.addActionListener(this);
	    tail.addActionListener(this);
	    clear.addActionListener(this);
	    quit.addActionListener(this);
	    this.addComponentListener(this);
	    this.addWindowListener(this);

	    Label speedLabel = new Label("Speed:");
	    gbc.gridy = 1; // Place the label in the next row
	    gbc.gridwidth = 1; // Reset gridwidth for label
	    gbc.weightx = 0.1; // Adjust weightx for label
	    control.add(speedLabel, gbc);
	    
	    // Modify GridBagConstraints for wider scrollbars
	    gbc.weightx = 4;
	   // gbc.gridwidth = GridBagConstraints.REMAINDER; // Make the scrollbar take up the rest of the row

	    // Speed scrollbar
	    SpeedScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);
	    SpeedScrollBar.setMaximum(SpeedSBmax);
	    SpeedScrollBar.setMinimum(SpeedSBmin);
	    SpeedScrollBar.setUnitIncrement(SBunit);
	    SpeedScrollBar.setValue(SpeedSBinit);
	    SpeedScrollBar.setVisibleAmount(SBvisible);
	    SpeedScrollBar.setBackground(Color.gray);
	    SpeedScrollBar.setPreferredSize(new Dimension(100, 20)); // Set preferred width and height
	    control.add(SpeedScrollBar, gbc);

	    // Label for speed scrollbar
	  
	    Label sizeLabel = new Label("Size:");
	    gbc.gridy = 1; // Place the label in the next row
	    control.add(sizeLabel, gbc);
	    // Size scrollbar
	    ObjSizeScrollBar = new Scrollbar(Scrollbar.HORIZONTAL);
	    ObjSizeScrollBar.setMaximum(MAXObj);
	    ObjSizeScrollBar.setMinimum(MINObj);
	    ObjSizeScrollBar.setUnitIncrement(SBunit);
	    ObjSizeScrollBar.setBlockIncrement(SBblock);
	    ObjSizeScrollBar.setValue(SOBJ);
	    ObjSizeScrollBar.setVisibleAmount(SBvisible);
	    ObjSizeScrollBar.setBackground(Color.gray);
	    ObjSizeScrollBar.setPreferredSize(new Dimension(100, 20)); // Set preferred width and height
	    gbc.gridy = 2; // Place the size scrollbar in the next row
	    control.add(ObjSizeScrollBar, gbc);

	  
	    control.setVisible(true);

	    // Adding components to the existing frame
	    add(sheet, BorderLayout.CENTER); // Add sheet panel to the center
	    add(control, BorderLayout.SOUTH); // Add control panel to the south

	    SpeedScrollBar.addAdjustmentListener(this);
	    ObjSizeScrollBar.addAdjustmentListener(this);

	    delay = (int) (DELAY +5/SpeedScrollBar.getValue());
	}

	private void SizeScreen()
	{
	//, scroll bars, and labels:
		//SpeedScrollBar.setLocation(i.left+BUTTONS,ScreenHeight+BUTTONHS+i.top);
		//ObjSizeScrollBar.setLocation(WinWidth-ScrollBarW-i.right-BUTTONS,ScreenHeight+BUTTONHS+i.top);
		//SPEEDL.setLocation(i.left+BUTTONS,ScreenHeight+BUTTONHS+BUTTONH+i.top);
		//SIZEL.setLocation(WinWidth-ScrollBarW-i.right,ScreenHeight+BUTTONHS+BUTTONH+i.top);
		//SpeedScrollBar.setSize(ScrollBarW,SCROLLBARH);
		//ObjSizeScrollBar.setSize(ScrollBarW,SCROLLBARH);
		//SPEEDL.setSize(ScrollBarW,SCROLLBARH);
		//Obj.setBounds(i.left,i.top,ScreenWidth,ScreenHeight);
		Obj.setSize(sheet.getWidth(), sheet.getHeight());
		
	}
	public void componentResized(ComponentEvent e)
	{
		
		 WinWidth = getWidth(); 
		 WinHeight = getHeight(); 
		MakeSheet(); 
		 SizeScreen();
		  
		 Obj.reSize(ScreenWidth, ScreenHeight);
		
		Rectangle r = new Rectangle();
		r.setBounds(Obj.walls.elementAt(0));
		int mr = r.x+r.width;
		int mb = r.y + r.height;
		
		for(int i = 0; i < Obj.walls.size(); i++) 
		{
		    r.setBounds(Obj.walls.elementAt(i));
		    mr = Math.max((r.x + r.width), mr);
		    mb = Math.max((r.y+ r.height),mb);
		}

		r.setBounds(Obj.ball);
		
		 mr = Math.max((r.x + r.width), mr);
		 mb = Math.max((r.y+ r.height),mb);
		 
		int sw = ScreenWidth;	
		 
		if(mr > ScreenWidth || mb > ScreenHeight) 
		{
			this.setSize(Math.max(mr+10, sw)+10, Math.max(mb+10, sw)+20); 
			
			setExtendedState(ICONIFIED); 
			setExtendedState(NORMAL);   
		}
			
		 
		 //this.setLocation(sheet.getWidth()-1,sheet.getHeight()-1);
		 
		 Perimeter.setBounds(getX(), getY(), sheet.getX(), sheet.getY());
	}
	public void componentHidden(ComponentEvent e) {}
	public void componentShown(ComponentEvent e) {}
	public void componentMoved(ComponentEvent e) {}
	
//action event handler
	public void actionPerformed(ActionEvent e)
	{
		Object source = e.getSource();
		if(source==start)
		{
			if(start.getLabel()=="pause")
			{
				start.setLabel("run");
				TimePause = true;
				thethread.interrupt();
				
			}
			else
			{
				start.setLabel("pause");
				TimePause = false;
			}
		}
		else if (source == shape)
		{
			if(!started)
			{
				Obj.Clear();
				Obj.repaint();
			}
			
			if(shape.getLabel()=="Circle")
			{
				shape.setLabel("Square");
				Obj.rectangle(false);
			}
			else
			{
				shape.setLabel("Circle");
				Obj.rectangle(true);
			}
			Obj.repaint();
		}
		else if (source == tail)
		{
			if(tail.getLabel()=="Tail")
			{
				tail.setLabel("No Tail");
				Obj.tail = true;
			}
			else
			{
				Obj.Clear();
				tail.setLabel("Tail");
				Obj.tail = false;
			}
		}
		else if (source==clear)
		{
			Obj.walls.removeAllElements();
			Obj.Clear();
			Obj.repaint();
			
		}
		else if (source == quit)
		{
			stop();
		}
	}
	
//scrollbar adjustments 
	public void adjustmentValueChanged(AdjustmentEvent e) 
	{
		int TS = e.getValue();
		TS = (TS/2)*2+1;
		int half = (TS-1)/2;
		
		Rectangle b = new Rectangle();
		
		b.setBounds(Obj.getX()-half-1, Obj.getY()-half-1, TS+2, TS+2);
		
		Scrollbar sb = (Scrollbar)e.getSource();
		if(sb == SpeedScrollBar)
		{
			//validate the value 
				//idk what this means exactly 
			//recalculate integer delay
			delay = (int) (DELAY + 5/SpeedScrollBar.getValue());
			
			//interupt Thread
			thethread.interrupt();
		}
		if(sb == ObjSizeScrollBar)
		{
			
			int i = 0;
			boolean ok = true;
			
			while(i < Obj.getWallSize() && ok)
			{
				Rectangle t = new Rectangle(Obj.walls.elementAt(i)); 
				
				if(t.intersects(b))
				{
					ok = false;
				}
				
				i++;
				
			}
			
			if(ok && !b.equals(Perimeter.intersection(b)))
			{
				 this.setSize(this.getWidth()+1,this.getHeight()+1);
				 this.setSize(this.getWidth()-1,this.getHeight()-1);
				Obj.ObjSize(TS);
			}
			else
			{
				sb.setValue(50);
			}
			
			//Obj.repaint();
		}
	}
	
//stop/start methods
	public void stop()
	{
		start.removeActionListener(this);
		shape.removeActionListener(this);
		clear.removeActionListener(this);
		tail.removeActionListener(this);
		quit.removeActionListener(this);
		this.removeComponentListener(this);
		this.removeWindowListener(this);
		
		SpeedScrollBar.removeAdjustmentListener(this);
		ObjSizeScrollBar.removeAdjustmentListener(this);
		
		run = false;
		thethread.interrupt();
		
		Obj.removeMouseListener(this);
		Obj.removeMouseMotionListener(this);
		
		dispose();
		System.exit(0);
	}
	public void start()
	{
		Obj.repaint();
		
		if(thethread == null)
		{
			thethread = new Thread(this);
			thethread.start();
		}
	}
	
	public void run()
	{
		while(run)	//while run flag is true 
		{
			//TimePause = false;
			if(!TimePause)	//if not paused
			{
				started = true;
				
				//try to sleep the thread for the delay time 
				try
				{
					Thread.sleep(delay);	
				}
				catch(InterruptedException e) {}
				
				//update the size in the object to the new size 
				//SObj = NS;
				//repaint the object
				Obj.repaint();
				
				//move the object to it's next location 
				Obj.move();
					//old size, x, and y are kept to erase the current object before drawing the new object when no tails 
			}
			
			//allows loop to interupt for pause 
			try
			{
				Thread.sleep(1);	
			}
			catch(InterruptedException e) {}
		}
	}
	
//validating object resizing
	public boolean checkSize(Objc Obj)
	{
		boolean goodSize = true;
		//get current x, y, and size from object 
		//calculate the right & bottom of the object 
		int bot = Obj.getObjectY() + (Obj.getObjectSize()-1)/2;
		int right = Obj.getObjectX() + (Obj.getObjectSize()-1)/2;
				
		if(bot > WinTop+ScreenHeight)
		{
			int i = WinTop + ScreenHeight - (Obj.getObjectSize()-1)/2; // set i to the border, minus the space needed for half object 
			Obj.setX(i);
			goodSize = false;
		}
		if(right > WinLeft+ScreenWidth)
		{
			int i = WinLeft + ScreenWidth - (Obj.getObjectSize()-1)/2; // set i to the border, minus the space needed for half object 
			Obj.setY(i);
			goodSize = false;
		}
		return goodSize;
	}
	
	
	
	
	// window methods
		public void windowClosing(WindowEvent e)
		{
			
			stop();			
		}
		// window listener ****goes into stop
		public void windowClosed (WindowEvent e) {}
		public void windowOpened(WindowEvent e) {}
		public void windowActivated(WindowEvent e) {}
		public void windowDeactivated(WindowEvent e){}
		public void windowIconified(WindowEvent e) {}
		public void windowDeiconified(WindowEvent e) {}
		
	//mouse methods 
		public void mouseDragged(MouseEvent e) {
			m2.setLocation(e.getX(), e.getY());
			
			
			
			Obj.rectX = Math.min(m1.x, m2.x);
			Obj.rectY = Math.min(m1.y, m2.y);
			
			Obj.rectWidth = Math.abs(m1.x-m2.x);
			Obj.rectHeight = Math.abs(m1.y-m2.y);
			
			db.setBounds(Obj.rectX, Obj.rectY, Obj.rectWidth, Obj.rectHeight);
			
			if(Perimeter.contains(db))
			{
				//Obj.setDragBox(db);
				Obj.repaint();
			}
		}

	

		public void mouseMoved(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		public void mouseClicked(MouseEvent e) {
			Point p = new Point(e.getX(), e.getY());
			
			
			
			int i = 0;
			
			int wallsize = Obj.walls.size();
			while(i < wallsize)
			{
				if(Obj.walls.elementAt(i).contains(p))
				{
					Obj.walls.remove(i);
					i=0;
				}
				wallsize = Obj.walls.size();
				i++;
			}
			
		}

		public void mouseEntered(MouseEvent e) {
			Obj.repaint();
			
		}

		public void mouseExited(MouseEvent e) {
			// TODO Auto-generated method stub
			
		}

		public void mousePressed(MouseEvent e) {
			m1.setLocation(e.getX(), e.getY());
			
		}

		public void mouseReleased(MouseEvent e) {
			Rectangle b = new Rectangle(Obj.ball);
			b.grow(1, 1);
			
			
			Rectangle addWall = new Rectangle(db);
			if(!addWall.intersects(b))
			{
				if(!addWall.intersection(Perimeter).equals(addWall))
				{
					
					Obj.walls.add(addWall);
					System.out.println("Rectangle just added " + db);
					for(int i = 0; i < Obj.walls.size(); i++)
					{
					    System.out.println("walls rectangle " + i + ": " + Obj.walls.elementAt(i));   
					}
					
					
					
					int i = 0;
					int wallsize = Obj.walls.size();
					while(i<wallsize-1)
					{
						if(addWall.contains(Obj.walls.elementAt(i)))
						{
							Obj.walls.remove(Obj.walls.elementAt(i));
							i=0;
						}
						if((Obj.walls.elementAt(i)).contains(addWall))
						{
							Obj.walls.remove(Obj.walls.lastElement());
							i=0;
						}
						i++;
						wallsize = Obj.walls.size();
					}
					for(i = 0; i < Obj.walls.size(); i++)
					{
					    System.out.println("walls rectangle " + i + ": " + Obj.walls.elementAt(i));   
					}
				}
				
			}
			Obj.rectX = 0;
			Obj.rectY = 0;
			Obj.rectWidth =0;
			Obj.rectHeight = 0;
			repaint();
		}
		
		
		

		
		
		
		
	
		
		
		
		
		
		
		
		
		
		
//main method
	public static void main(String[] args)
	{
		
		BouncingBall b = new BouncingBall();
		//PanelMouse p = b.new PanelMouse();
		
	}




	
	
	
	

}