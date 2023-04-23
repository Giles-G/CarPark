#ifndef FULLSIGN_HPP_
#define FULLSIGN_HPP_

class FullSign {
   public:
    FullSign() = default;

    bool full() {
        return lightOn_;
    }

    void SwithOn() {
        lightOn_ = true;
    }

    void SwitchOff() {
        lightOn_ = false;
    }

   private:
    bool lightOn_;
};

#endif  // FULLSIGN_HPP_