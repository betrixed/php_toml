<?php

/**
 * class DayTime 
 * 
 * Stores time of day as fraction of 24 hour period
 * stored as value from 0.0 <= x < 1.0 
 * The Toml Parser expects a class
 * like this to exist for time values.
 * A php_daytime extension that does this exists,
 * with very much the same functionality.
 * 
 * 
 * @author michael
 */

class DayTime
{
    public float $val = 0.0;
    
    const SEC_AUTO = 0;
    const SEC_INT = 1;
    const SEC_DEC = 2;
    const SEC_NONE = 4;


    public function __construct(?string $t24 = null) {
        if (!empty($t24)) {
            $this->val = daytime_str($t24);
        }
    }

    public function setValue(float $val) {
        if ($val < 0.0 || $val >= 1.0) {
            throw new Exception("DayTime must be >= 0.0 and < 1.0");
        }
        $this->val = $val;

    }
    public function value() : float
    {
        return $this->val;
    }
        /**
     * Set conventional of day, modulus 24
     * @param int $hours 0-23
     * @param int $mins  0-59
     * @param int $seconds 0-59
     * @param double $fraction 0 - 0.999999
     */

    public function set(int $hours, int $mins, float $seconds) {
        $this->setValue(daytime_set($hours,$mins,$seconds));
        
    }
    /**
     * String assumed to be compatible with
     * regular expression
     * (\\d{2}:\\d{2}(:\\d{2})?(\\.\\d+)?)
     */
    public function str(string $t24) {
        $this->setValue(daytime_str($t24));
    }
    /**
     * Return 
     * @return string
     */
    public function format(int $flag = 0) : string {
        return daytime_format($this->val, $flag);
    }
    
    public function split(int &$h24, int &$min, float &$sec) {
        daytime_split($h24,$min,$sec);
    }

    public function __toString() {
        return $this->format();
    }
}


function daytime_format(float $val, int $flags = 0) : string 
{
        $h24 = 0;
        $min = 0;
        $sec = 0.0;
        daytime_split($val,$h24,$min,$sec);
        switch($flags) {
            case DayTime::SEC_INT:
                return sprintf("%02d:%02d:%02.0f", $h24,$min,$sec);
            case DayTime::SEC_DEC:
                return sprintf("%02d:%02d:%08.6f",$h24,$min,$sec);
            case DayTime::SEC_NONE:
                return sprintf("%02d:%02d", $h24,$min);
            case DayTime::SEC_AUTO:
            default:
                if ($sec !== 0) {
                    if ($sec - floor($sec) > 0.0) {
                         return sprintf("%02d:%02d:%8.6f",$h24,$min,$sec);
                    }
                    else {
                        return sprintf("%02d:%02d:%02.0f",$h24,$min,$sec);
                    }
                }
                return sprintf("%02d:%02d", $h24,$min);
        }
}

function daytime_str(string $t24) : float {
        $i = stripos($t24,":");
        if ($i === 2) {
            $hours = intval(substr($t24,0,2));
            $mins = intval(substr($t24,3,2));
        }
        else {
            throw new Exception("Invalid time string");
        }
        $i = stripos($t24,":",$i+1);
        if ($i == 5) {
            $secs = floatval(substr($t24,6));
        }
        else {
            $secs = 0;
        }
        return daytime_set($hours,$mins,$secs);
}

/* 
 * return hours, mins and seconds as fractional number of days
 */

function daytime_set(int $hours, int $mins, float $seconds) : float {
        return ($hours*60.0*60.0+$mins*60.0+$seconds)/(24.0*60*60.0);
}

function daytime_split(float $val, int &$h24, int &$min, float &$sec) {
    $frs = $val * 24.0 * 60.0 * 60.0;
    $h24 = floor($frs / (60.0 * 60.0));
    $min =  floor($frs / 60.0) - $h24 * 60;
    $sec =  $frs - $h24*60*60 - $min*60;
}
