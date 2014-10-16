import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;
import com.sun.jna.ptr.IntByReference;

import java.util.Arrays;
import java.util.List;

interface MyCLibrary extends Library {

    public static class MyStruct extends Structure implements Structure.ByReference {
        public String fileName;
        public long fileSize;

        @Override
        protected List getFieldOrder() {
            return Arrays.asList("fileName", "fileSize");
        }
    }
    MyCLibrary INSTANCE = (MyCLibrary) Native.loadLibrary("randomjna", MyCLibrary.class);

    int randomNumber(int bound);
    MyStruct list_files(String directory, IntByReference numElements);
    void free_struct(MyStruct.ByReference struct, int numElements);
}


public class JavaNativeAccess {
    public static void main(String[] args) {
        try {
            System.out.println("Random number from C is: " + MyCLibrary.INSTANCE.randomNumber(150));

            // get list of files

            IntByReference nElements = new IntByReference();
            MyCLibrary.MyStruct struct = MyCLibrary.INSTANCE.list_files(".", nElements);
            MyCLibrary.MyStruct[] structArr = (MyCLibrary.MyStruct[]) struct.toArray(nElements.getValue());


            System.out.println("");
            System.out.println("----");
            System.out.println("");
            for (int i = 0; i < nElements.getValue(); i++) {
               System.out.println(structArr[i].fileName + " --> " + structArr[i].fileSize);
            }

            MyCLibrary.INSTANCE.free_struct(struct, nElements.getValue());
        } catch (UnsatisfiedLinkError e) {
            System.out.println("Exception" + e);
        }
    }
}
