import java.awt.*;
import java.awt.event.*;
import java.io.*;

public class Window extends Frame implements WindowListener, ActionListener {
    private static final long serialVersionUID = 1L;

    // GUI Components
    Label sourceLabel = new Label("Source:");
    Label targetDir = new Label("Select Target Directory:");
    Label fileLabel = new Label("File Name:");
    Label messages = new Label("");

    Button targetButton = new Button("Target:");
    Button okayButton = new Button("OK");

    TextField fileName = new TextField(80);
    java.awt.List list = new java.awt.List(13);

    File curDir;

    // Constructor
    Window() {
        // Setup Frame
        setTitle("Directory Navigation");
        setSize(800, 600);
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        addWindowListener(this);

        // Add List
        c.gridx = 0;
        c.gridy = 0;
        c.gridwidth = 2;
        c.gridheight = 10;
        c.fill = GridBagConstraints.BOTH;
        add(list, c);
        list.addActionListener(this);

        // Add Source Label
        c.gridx = 0;
        c.gridy = 10;
        c.gridwidth = 1;
        c.gridheight = 1;
        add(sourceLabel, c);

        // Add Target Button
        c.gridx = 0;
        c.gridy = 11;
        add(targetButton, c);
        targetButton.addActionListener(this);

        // Add Target Directory Label
        c.gridx = 1;
        c.gridy = 11;
        add(targetDir, c);

        // Add File Label
        c.gridx = 0;
        c.gridy = 12;
        add(fileLabel, c);

        // Add File Name TextField
        c.gridx = 1;
        c.gridy = 12;
        add(fileName, c);
        fileName.addActionListener(this);

        // Add OK Button
        c.gridx = GridBagConstraints.RELATIVE;
        c.gridy = 12;
        c.gridwidth = 2;
        add(okayButton, c);
        okayButton.addActionListener(this);

        // Add Messages Label
        c.gridx = 0;
        c.gridy = 14;
        c.gridwidth = 2;
        add(messages, c);

        setVisible(true);
    }

    // WindowListener methods
    public void windowClosing(WindowEvent e) {
        dispose();
    }

    // ActionListener method
    public void actionPerformed(ActionEvent e) {
        Object source = e.getSource();

        // Handle actions based on event source
        if (source == targetButton) 
        {
            // Update target directory label
            targetDir.setText(curDir.getAbsolutePath());
        } 
        else if (source == list) 
        {
            // Handle directory/file selection
            String selectedItem = list.getSelectedItem();
            if (selectedItem != null) 
            {
                File selectedFile = new File(curDir, selectedItem);
                if (selectedFile.isDirectory()) 
                {
                    // Update current directory and refresh list
                    curDir = selectedFile;
                    refreshList();
                    // Enable target button
                    targetButton.setEnabled(true);
                } 
                else 
                {
                    // Update source label
                    sourceLabel.setText(selectedItem);
                }
            }
        } 
        else if (source == okayButton || source == fileName) 
        {
            // Handle OK button or Enter key pressed in fileName field
            String targetFileName = fileName.getText();
            if (targetFileName.isEmpty()) 
            {
                messages.setText("Target file not specified.");
            } 
            else 
            {
                // Copy file logic
                File sourceFile = new File(curDir, sourceLabel.getText());
                File targetFile = new File(curDir, targetFileName);
                try {
                    copyFile(sourceFile, targetFile);
                    messages.setText("File copied.");
                } catch (IOException ex) {
                    messages.setText("Error copying file: " + ex.getMessage());
                }
            }
        }
    }

    // Refresh directory list
    private void refreshList() 
    {
        list.removeAll();
        list.add("..");
        String[] files = curDir.list();
        if (files != null) {
            for (String file : files) {
                if (new File(curDir, file).isDirectory()) 
                {
                    list.add(file + "+");
                } 
                else 
                {
                    list.add(file);
                }
            }
        }
    }

    // Copy file method
    private void copyFile(File source, File target) throws IOException 
    {
        try (BufferedReader reader = new BufferedReader(new FileReader(source));
             PrintWriter writer = new PrintWriter(target)) 
        {
            String line;
            while ((line = reader.readLine()) != null) 
            {
                writer.println(line);
            }
        }
    }

    // Unused WindowListener methods
    public void windowOpened(WindowEvent e) {}
    public void windowClosed(WindowEvent e) {}
    public void windowActivated(WindowEvent e) {}
    public void windowDeactivated(WindowEvent e) {}
    public void windowIconified(WindowEvent e) {}
    public void windowDeiconified(WindowEvent e) {}
}
