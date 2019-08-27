package utils

import "bytes"
import	"fmt"
func IntsToString(integers []int) string {
	var buf bytes.Buffer
	buf.WriteByte('[')
	for i, v := range integers {
		if i > 0 {
			buf.WriteString(", ")
		}
		fmt.Fprintf(&buf, "%d", v)
	}
	buf.WriteByte(']')

	return buf.String()
}