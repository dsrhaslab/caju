#include <cassert>
#include <cstddef>
#include <fcntl.h>
#include <memory>
#include <string>
#include <unistd.h>

int main(int argc, char* argv[]) {

    std::string data_1(
R"( Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse mi eros, laoreet at tincidunt quis, hendrerit vitae sem. Mauris auctor est hendrerit nisi semper lacinia. Maecenas enim ipsum, maximus vitae nisi sed, feugiat gravida elit. Fusce in sem nunc. Integer vulputate sit amet eros ac sodales. Sed nunc metus, placerat id lacinia ut, euismod ut tellus. Quisque ac scelerisque nunc. Etiam id lectus molestie sem suscipit tempor. Donec libero felis, tristique nec porta at, hendrerit auctor ipsum. Nullam magna risus, malesuada eget est id, faucibus hendrerit purus.
Etiam ut turpis et quam dapibus malesuada blandit non nisi. Aliquam sem velit, sagittis a eros ut, blandit scelerisque ex. Morbi ullamcorper nibh id tortor rutrum, non elementum odio sagittis. Suspendisse dapibus sollicitudin nisl eu pulvinar. Aliquam vel odio vitae erat malesuada blandit. Duis in tellus rhoncus, porttitor mi vel, sagittis tortor. Maecenas fermentum eget orci sit amet faucibus. Nulla blandit nulla a neque consectetur gravida. Vestibulum faucibus luctus purus eu viverra. Maecenas sollicitudin consequat lacus sit amet molestie. Integer viverra ut enim et pulvinar. Aliquam venenatis enim justo, vel lacinia ex tristique sit amet. Phasellus eros nibh, hendrerit aliquet libero eget, suscipit varius metus.
Etiam feugiat eleifend cursus. Aliquam nec augue vitae orci consectetur eleifend aliquet quis turpis. Nulla in eleifend nisi. Donec dapibus mi ac convallis eleifend. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Morbi sit amet pharetra diam. Donec vitae sollicitudin nulla, id sagittis eros. Nunc consequat purus non felis rhoncus euismod. Suspendisse varius odio in feugiat sodales. Etiam elit mauris, mattis quis tempor at, rhoncus in leo. Nam dictum tellus id mattis convallis. Nam eget ipsum eu odio pulvinar porttitor.
Aenean in tellus facilisis, vehicula ipsum at, bibendum risus. In in lacinia sem. Ut posuere libero sed purus auctor, ac ultricies massa eleifend. Aenean iaculis sem orci, interdum tincidunt metus auctor sed. Sed diam lectus, dapibus sed leo vitae, eleifend vulputate tellus. Cras a dui non enim dictum fringilla. Proin in varius orci, nec dignissim eros. Curabitur elementum lorem sed lacus tempor, vel varius enim lobortis. Aliquam at gravida felis. Nunc facilisis felis ac eleifend eleifend. Nam vitae vestibulum turpis, in dapibus purus.
Ut vel odio at tortor condimentum imperdiet. In id lobortis tellus, vitae lobortis massa. Vivamus molestie at felis malesuada suscipit. Quisque et enim et nunc dignissim lobortis. Mauris pretium tristique nunc, ut pulvinar est placerat eget. Integer molestie elementum pellentesque. Aliquam consectetur nulla in nunc viverra, eget fringilla massa consectetur. In libero orci, venenatis eu magna pellentesque, aliquam convallis felis. Maecenas iaculis placerat risus. Mauris scelerisque orci ut odio semper euismod. Sed sed pharetra arcu. Integer in iaculis enim. Etiam cursus lectus nisi, commodo euismod mauris malesuada et.)""\n");

    int fd = open("/tmp/test_file", O_CREAT | O_RDWR, 0644);

    // assert(fd > 0);

    size_t bytes_written = write(fd, data_1.c_str(), data_1.size());

    // assert(bytes_written > 0);

    auto buffer = std::make_unique<char*>(new char[data_1.size()]);

    auto bytes_read = read(fd, buffer.get(), data_1.size());

    // assert(bytes_read > 0);

    close(fd);

    return 0;
}
