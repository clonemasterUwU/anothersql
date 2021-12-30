#include <memory>
#include <cassert>
#include "storage/DataBox.h"

DataBox fromBinary(std::ifstream &inFile, u32 index) {
    if (index == 0) {
        DataBox ret{std::in_place_type<i32>};
        inFile.read((char *) get_if<i32>(&ret), sizeof(i32));
        return ret;
    } else if (index == 1) {
        DataBox ret{std::in_place_type<i64>};
        inFile.read((char *) get_if<i64>(&ret), sizeof(i64));
        return ret;
    } else if (index == 2) {
        DataBox ret{std::in_place_type<f32>};
        inFile.read((char *) get_if<f32>(&ret), sizeof(f32));
        return ret;
    } else if (index == 3) {
        DataBox ret{std::in_place_type<f64>};
        inFile.read((char *) get_if<f64>(&ret), sizeof(f64));
        return ret;
    }else if(index==4){
        DataBox ret{std::in_place_type<bool>};
        inFile.read((char *) get_if<bool>(&ret), sizeof(bool));
        return ret;
    }else if(index==5){
        u32 size;
        inFile.read((char *) (&size), sizeof(u32));
        std::unique_ptr<char[]> temp = std::make_unique<char[]>(size+1);
        inFile.read(temp.get(),size);
        temp[size]='\0';
        DataBox ret{std::in_place_type<std::pair<u32,std::string >>,size,std::string (temp.get())};
        return ret;
    }
    assert(false);
}

void toBinary(std::ofstream &outFile, const DataBox &value) {
    const void* ptr;
    if((ptr = std::get_if<i32>(&value))){
        outFile.write((char*)ptr,sizeof (i32));
    } else if((ptr = std::get_if<i64>(&value))){
        outFile.write((char*)ptr,sizeof (i64));
    }else if((ptr = std::get_if<f32>(&value))){
        outFile.write((char*)ptr,sizeof (f32));
    }else if((ptr = std::get_if<f64>(&value))){
        outFile.write((char*)ptr,sizeof (f64));
    }else if((ptr = std::get_if<bool>(&value))){
        outFile.write((char*)ptr,sizeof (bool));
    } else {
        assert(value.index()==5);
        auto& [size,pt] = *std::get_if<std::pair<u32,std::string>>(&value);
        outFile.write((char*)&size,sizeof (u32));
        outFile.write(pt.c_str(),size);
    }
};

