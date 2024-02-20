#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

namespace basic {

/**
 * @brief message content encapsulation
 */
class Message {
   private:  
     std::string mName;
     std::string mGroup;
     std::string mText;

   public: 
      Message(std::string name, std::string group, std::string text) {
      this->mName = name;
      this->mGroup = group;
      this->mText = text;
      }

      virtual ~Message() {}

      bool operator== (Message& rhs) const {
         if ( this == &rhs ) return  true; // same addr
         else 
            return (this->mName == rhs.mName && this->mGroup == rhs.mGroup && 
                     this->mText == rhs.mText);
      }
     
      std::string name() const {return this->mName;}
      std::string group() const {return this->mGroup;}
      std::string text() const {return this->mText;}

      void name(std::string name) {this->mName = name;}
      void group(std::string group) {this->mGroup = group;}
      void text(std::string text) {this->mText = text;}

      // @Author : Armaghan

   std::string serialize() const {
    // Using a simple delimiter (e.g., "|") to separate fields.
    // Ensure this matches the java server's expected format.
    return mName + "|" + mGroup + "|" + mText;
}

// Static method for deserialization (if ever needed on the C++ side)
   static Message deserialize(const std::string& serializedMessage) {
    std::string parts[3];
    size_t pos = 0, startPos = 0, partIndex = 0;

    while ((pos = serializedMessage.find('|', startPos)) != std::string::npos && partIndex < 3) {
        parts[partIndex++] = serializedMessage.substr(startPos, pos - startPos);
        startPos = pos + 1;
    }

    if (partIndex < 3) // Assuming the last part goes to the end of the string
        parts[partIndex] = serializedMessage.substr(startPos);

    return Message(parts[0], parts[1], parts[2]);
}
  

};

} // ns

#endif
