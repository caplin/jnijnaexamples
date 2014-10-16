/**
 * Created by chsitter on 16/10/14.
 */
public class JavaNativeInterface {
    static {
       System.loadLibrary("randomjni");
    }

    public static class FileListItem {

       public FileListItem(String fileName, long fileSize) {
          this.fileName = fileName;
          this.fileSize = fileSize;
       }

       String fileName;
       long   fileSize;
    }

    public native int randomNumber(int bounds);
    public native FileListItem[] listFiles(String directory); 


    public void printFileList(String directory) {
       FileListItem[] files = listFiles(directory);

       for( int i = 0; i < files.length; i++ ) {
         System.out.println(files[i].fileName + " --> " + files[i].fileSize);
       }
    }

    public static void main(String[] args) {

        JavaNativeInterface obj = new JavaNativeInterface();
        System.out.println("Random number from C is : " + obj.randomNumber(150));

        System.out.println("");
        System.out.println("----");
        System.out.println("");

        obj.printFileList(".");
    }
}
